#include "utils.h"
#include "version.h"
#include "constants.h"
#include "commands.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

bool parse_args(int argc, const char **argv) {
	if (argc < 2 || !isalpha(argv[1][0])) {
		fprintf(stderr, "Usage: tmail <command> [options]\n");
		return false;
	}

	const char *cmd = argv[1];
	execute_cmd(cmd, argc - 2, (const char **)(argv + 2));

	return false;
}

/* Cryptography tools */

/**
 * Generate an encryption key based on machine characteristics
 *
 * Parameters:
 *  key_output - the buffer to store the generated key
 *  key_size   - the size of the output buffer
 *
 * Return:
 *  true if the key was successfully generated, false otherwise
 */
 
bool get_machine_key(char *key_output, size_t key_size) {
    if (key_size < MACHINE_KEY_LENGTH) { // 64-char has + null terminator
        return false;
    }

    char machine_info[1024] = {0};
    struct utsname sys_info;

    if (uname(&sys_info) != 0) {
        return false;
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        return false;
    }

    // Generate key using various machine properties
    snprintf(machine_info, sizeof(machine_info),
            "%s-%s-%s-%s-%ld",
            sys_info.sysname,   // OS name
            sys_info.nodename,  // Network node hostname
            sys_info.machine,   // Hardware architecture
            hostname,           // Hostname
            (long)getuid()      // User ID
    );

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)machine_info, strlen(machine_info), hash);

    // Convert to hex string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        snprintf(key_output + (i * 2), 3, "%02x", hash[i]);
    }
    key_output[64] = '\0';

    return true;
}

bool encrypt_data(const char* data, const char* key, char *output,
        size_t output_size) {
    // Convert hex key to binary
    unsigned char binary_key[AES_KEY_SIZE];
    for (int i = 0; i < AES_KEY_SIZE; i++) {
        sscanf(key + (i * 2), "%2hhx", &binary_key[i]);
    }

    // Generate random IV
    unsigned char iv[AES_IV_SIZE];
    if (!RAND_bytes(iv, sizeof(iv))) { return false; }

    // Setup encryption
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) { return false; }
 
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, binary_key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    // Encrypt data
    unsigned char encrypted[ENCRYPTED_DATA_BUFFER_SIZE];
    int len, total_len;

    if (EVP_EncryptUpdate(ctx, encrypted, &len, (unsigned char*)data,
                strlen(data)) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    total_len = len;

    if (EVP_EncryptFinal_ex(ctx, encrypted + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
    }
    total_len += len;

    EVP_CIPHER_CTX_free(ctx);

    // Check output buffer size (IV + encrypted data, all hex)
    if (output_size < (size_t)(AES_IV_SIZE + total_len) * 2 + 1) { 
        return false;
    }

    // Convert IV + encrypted data to hex string
    for (int i = 0; i < AES_IV_SIZE; i++) {
        snprintf(output + (i * 2), 3, "%02x", iv[i]);
    }

    for (int i = 0; i < total_len; i++) {
        snprintf(output + AES_IV_HEX_LENGTH + (i * 2), 3, "%02x", encrypted[i]);
    }

    return true;
}

bool decrypt_data(const char *data, const char *key, char *output,
        size_t output_size) {
    // Convert hex key to binary
    unsigned char binary_key[AES_KEY_SIZE];
    for (int i = 0; i < AES_KEY_SIZE; i++) {
        sscanf(key + (i * 2), "%2hhx", &binary_key[i]);
    }

    // Extract IV from first part of data (32 hex chars = 16 bytes)
    unsigned char iv[AES_IV_SIZE];
    for (int i = 0; i < AES_KEY_SIZE; i++) {
        sscanf(data + (i * 2), "%2hhx", &iv[i]);
    }

    // Extract encrypted portion
    int data_hex_len = strlen(data) - AES_IV_HEX_LENGTH; // Subtract IV portion
    unsigned char encrypted[ENCRYPTED_DATA_BUFFER_SIZE];
    int encrypted_len = data_hex_len / 2;

    for (int i = 0; i < encrypted_len; i++) {
        sscanf(data + AES_IV_HEX_LENGTH + (i * 2), "%2hhx", &encrypted[i]);
    }

    // Setup decryption
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) { return false; }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, binary_key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    unsigned char decrypted[ENCRYPTED_DATA_BUFFER_SIZE];
    int len, total_len;

    if (EVP_DecryptUpdate(ctx, decrypted, &len, encrypted, encrypted_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    total_len = len;

    if (EVP_DecryptFinal_ex(ctx, decrypted + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    total_len += len;

    EVP_CIPHER_CTX_free(ctx);

    // Copy to output buffer
    if (output_size <= (size_t)total_len) {
        return false;
    }

    memcpy(output, decrypted, total_len);
    output[total_len] = '\0';

    return true;
}

/* Console messages */

/**
 * Print a help message to stdout, containing a list of commands and
 * their purposes.
 *
 * Parameters:
 *  none
 *
 * Return:
 *  void
 */
void print_help(void) {
	printf("login   Login to an email account\n");
}

/**
 * Print the current application version to stdout
 *
 * Parameters:
 *  none
 *
 * Return:
 *  void
 */
void print_version(void) {
	printf("tmail version %s\n", xstr(VERSION));
}
