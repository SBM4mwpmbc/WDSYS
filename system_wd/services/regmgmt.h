#ifndef REGMGMT_H
#define REGMGMT_H

#ifdef __cplusplus
extern "C" {
#endif

#define WD_REG_SUCCESS          0
#define WD_REG_GENERAL_ERROR   -1
#define WD_REG_NOT_FOUND       -2
#define WD_REG_ALREADY_EXISTS  -3
#define WD_REG_INVALID_KEY     -4
#define WD_REG_INVALID_VALUE   -5
#define WD_REG_STORAGE_ERROR   -6

int wd_reg_init(void);

int wd_reg_set(
    const char* key,
    const char* value
);

int wd_reg_get(
    const char* key,
    char* buffer,
    unsigned long buffer_size
);

int wd_reg_exists(
    const char* key
);

int wd_reg_remove(
    const char* key
);

void wd_reg_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif