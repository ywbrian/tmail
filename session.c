#include "session.h"

bool is_session_valid(void) {
	char config_path[512];
	snprintf(config_path, sizeof(config_path), "%s/%s", getenv("HOME"),
	         CONFIG_FILE);

	FILE *f = fopen(config_path, "rb");
	if (!f)
		return false;

	session_t session;
	if (fread(&session, sizeof(session), 1, f) != 1) {
		fclose(f);
		return false;
	}
	fclose(f);

	// Check if session expired
	time_t now = time(NULL);
	if (difftime(now, session.last_login) >
	    (session.session_timeout_hours * 3600)) {
		return false;
	}

	return true;
}
