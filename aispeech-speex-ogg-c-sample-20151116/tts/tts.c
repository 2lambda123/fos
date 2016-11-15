#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cJSON.h>
#include <agn_hmac_sha1.h>

/* Converts a hex character to its integer value */
char from_hex(char ch)
{
	return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

/* Converts an integer value to its hex character*/
char to_hex(char code)
{
	static char hex[] = "0123456789abcdef";
	return hex[code & 15];
}

/* Returns a url-encoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *url_encode(char *str)
{
	char *pstr = str;
	char *buf = malloc(strlen(str) * 3 + 1);
	char *pbuf = buf;
	while (*pstr) {
		if (isalnum(*pstr) ||
			*pstr == '-' ||
			*pstr == '_' ||
			*pstr == '.' ||
			*pstr == '~')
			*pbuf++ = *pstr;
		else if (*pstr == ' ') 
			*pbuf++ = '+';
		else 
			*pbuf++ = '%',
				*pbuf++ = to_hex(*pstr >> 4),
				*pbuf++ = to_hex(*pstr & 15);
		pstr++;
	}
	*pbuf = '\0';
	return buf;
}

/* Returns a url-decoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *url_decode(char *str)
{
	char *pstr = str;
	char *buf = malloc(strlen(str) + 1);
	char *pbuf = buf;
	while (*pstr) {
		if (*pstr == '%') {
			if (pstr[1] && pstr[2]) {
				*pbuf++ = from_hex(pstr[1]) << 4
						| from_hex(pstr[2]);
				pstr += 2;
			}
		} else if (*pstr == '+') { 
			*pbuf++ = ' ';
		} else {
			*pbuf++ = *pstr;
		}
		pstr++;
	}
	*pbuf = '\0';
	return buf;
}

char *tts_url_output(char *cfg, char *text)
{
	char *appkey;
	char *secretkey;
	char timestamp[128] = {0};
	char *userid;
	int samplebytes;
	int samplerate;
	int channel;
	int speechvolume;
	char *coretype;
	float speechrate;
	int rightmargin;
	int realback;
	char *res;
	char *server;
	char *port;
	char *audiotype;
	char buf[1024] = {0};
	char buff[1024] = {0};
	char *url = malloc(2048);;
	/*XXX:*/
	char *authId = "11123343434421";

	cJSON *root = cJSON_Parse(cfg);
	cJSON *tmp = cJSON_GetObjectItem(root, "appKey");
	appkey = tmp->valuestring;

	tmp = cJSON_GetObjectItem(root, "secretKey");
	secretkey = tmp->valuestring;

	tmp = cJSON_GetObjectItem(root, "userId");
	userid = tmp->valuestring;

	tmp = cJSON_GetObjectItem(root, "coretype");
	coretype = tmp->valuestring;

	tmp = cJSON_GetObjectItem(root, "cloud");
	cJSON *t = cJSON_GetObjectItem(tmp, "server");
	server = t->valuestring;
	t = cJSON_GetObjectItem(tmp, "port");
	port = t->valuestring;

	tmp = cJSON_GetObjectItem(root, "audio");
	t = cJSON_GetObjectItem(tmp, "sampleBytes");
	samplebytes = t->valueint;
	t = cJSON_GetObjectItem(tmp, "sampleRate");
	samplerate = t->valueint;
	t = cJSON_GetObjectItem(tmp, "channel");
	channel = t->valueint;
	t = cJSON_GetObjectItem(tmp, "audioType");
	audiotype = t->valuestring;

	tmp = cJSON_GetObjectItem(root, "request");
	t = cJSON_GetObjectItem(tmp, "speechVolume");
	speechvolume = t->valueint;
	t = cJSON_GetObjectItem(tmp, "speechRate");
	speechrate = t->valueint;
	t = cJSON_GetObjectItem(tmp, "rightMargin");
	rightmargin = t->valueint;
	t = cJSON_GetObjectItem(tmp, "realBack");
	realback = t->valueint;
	t = cJSON_GetObjectItem(tmp, "res");
	res = t->valuestring;

	sprintf(timestamp, "%d", (int)rand);
	sprintf(buf, "%s\n%s\n%s\n%s", appkey, timestamp, secretkey, authId);
	char *sig = hmac_sha1(secretkey, buf);
	char *tt = url_encode(text);

	sprintf(buff, "applicationId=%s&timestamp=%s&sig=%s&params="
			"{\"app\": {\"userId\": \"%s\"}, \"audio\": "
			"{\"sampleBytes\": %d, \"sampleRate\": %d, "
			"\"channel\": %d, \"audioType\": \"%s\"}, "
			"\"request\": {\"speechVolume\": %d, "
			"\"coreType\": \"%s\", \"speechRate\": %f, "
			"\"rightMargin\": %d, \"realBack\": %d, "
			"\"res\": \"%s\",\"refText\": \"%s\"}}",
			appkey, timestamp, sig, userid, samplebytes,
			samplerate, channel, audiotype, speechvolume,
			coretype, speechrate, rightmargin, realback, res, tt);

	sprintf(url, "http://%s:%s/%s/%s?%s",
			   server, port, coretype, res, buff);
	 cJSON_Delete(root);
	 free(tt);
	 free(sig);
	return url;
}