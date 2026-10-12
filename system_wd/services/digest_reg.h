#ifndef DIGEST_REG_H
#define DIGEST_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#define WD_DIGEST_SUCCESS          0
#define WD_DIGEST_GENERAL_ERROR   -1
#define WD_DIGEST_NOT_FOUND       -2
#define WD_DIGEST_INVALID_ITEM    -3
#define WD_DIGEST_INVALID_TYPE    -4
#define WD_DIGEST_ALREADY_EXISTS  -5
#define WD_DIGEST_STORAGE_ERROR   -6
#define WD_DIGEST_INVALID_VALUE   -7

#define WD_DIGEST_FOOD             1
#define WD_DIGEST_DRINK            2
#define WD_DIGEST_SNACK            3

int wd_digest_init(void);

void wd_digest_shutdown(void);

int wd_digest_register_item(
    const char* name,
    int category
);

int wd_digest_item_exists(
    const char* name
);

int wd_digest_remove_item(
    const char* name
);

int wd_digest_consume(
    const char* name
);

int wd_digest_clear_state(void);

int wd_digest_get_category(
    const char* name
);

int wd_digest_get_effect(
    const char* name,
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_mood(
    const char* name,
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_sugar(
    const char* name,
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_energy(
    const char* name,
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_hydration(
    const char* name,
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_fullness(
    const char* name,
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_current_item(
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_current_effect(
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_current_mood(
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_current_sugar(
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_current_energy(
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_current_hydration(
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_current_fullness(
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_reset_effects(void);

int wd_digest_is_active(void);

int wd_digest_get_state_summary(
    char* buffer,
    unsigned long buffer_size
);

int wd_digest_get_character_message(
    char* buffer,
    unsigned long buffer_size
);


#ifdef __cplusplus
}
#endif

#endif   