#include "email.h"

#include <curl/curl.h>

#define GMAIL_IMAP_SERVER "imaps://imap.gmail.com:993"
#define GMAIL_SMTP_SERVER "imaps://smtp.gmail.com:465"

bool login_to_gmail(const char *email, const char *password) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, email);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "EXAMINE INBOX");

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return (res == CURLE_OK);
}
