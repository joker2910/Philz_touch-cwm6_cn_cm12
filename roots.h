/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RECOVERY_ROOTS_H_
#define RECOVERY_ROOTS_H_

#include "common.h"
#include <fs_mgr.h>

#ifdef __cplusplus
extern "C" {
#endif

// Load and parse volume data from /etc/recovery.fstab.
void load_volume_table();

// Return the fstab_rec* record for this path (or NULL).
fstab_rec* volume_for_path(const char* path);

// Make sure that the volume 'path' is on is mounted.  Returns 0 on
// success (volume is mounted).
int ensure_volume_mounted(fstab_rec* v);
int ensure_path_mounted(const char* path);

// Make sure that the volume 'path' is on is mounted.  Returns 0 on
// success (volume is unmounted);
int ensure_volume_unmounted(fstab_rec *v);
int ensure_path_unmounted(const char* path);

// Reformat the given volume (must be the mount point only, eg
// "/cache"), no paths permitted.  Attempts to unmount the volume if
// it is mounted.
int format_volume(const char* volume, bool force = false);

// Ensure that all and only the volumes that packages expect to find
// mounted (/tmp and /cache) are mounted.  Returns 0 on success.
int setup_install_mounts();

// Conditionally wipes the /persistent partition if it's marked
// to wipe. Returns -1 on failure, 1 if the partition was wiped
// and 0 if the partition was not wiped.
int erase_persistent_partition();

char* get_android_secure_path();
int get_num_volumes();

struct storage_item {
    fstab_rec*  vol;
    char*       label;
    char*       path;
};

int is_data_media();
storage_item* get_storage_items();
void free_storage_items(storage_item* items);

#ifdef __cplusplus
}
#endif

#define MAX_NUM_MANAGED_VOLUMES 10

#endif  // RECOVERY_ROOTS_H_
