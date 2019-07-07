/*
 * nunchukapi.h
 *
 *  Created on: Aug 13, 2018
 *      Author: qspace
 */

#ifndef NUNCHUKAPI_H_
#define NUNCHUKAPI_H_

// Whether to disable encryption. Enabling encryption means that every packet must be decrypted, which wastes cpu cycles. Cheap Nunchuk clones have problems with the encrypted init sequence, so be sure you know what you're doing
#define NUNCHUK_DISABLE_ENCRYPTION

int nunchuk_i2cInit(void);

int nunchuk_read(char* buf, unsigned char numBytes);

int nunchuk_write(char* buf, unsigned char numBytes);

int nunchuk_HandleData(void);

#endif /* NUNCHUKAPI_H_ */
