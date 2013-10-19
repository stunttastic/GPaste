/*
 *      This file is part of GPaste.
 *
 *      Copyright 2013 Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
 *
 *      GPaste is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      GPaste is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with GPaste.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined (__G_PASTE_H_INSIDE__) && !defined (G_PASTE_COMPILATION)
#error "Only <gpaste.h> can be included directly."
#endif

#ifndef __GPASTE_MACROS_H__
#define __GPASTE_MACROS_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define G_PASTE_VISIBLE __attribute__((visibility("default")))

#define G_PASTE_CLEANUP(fun) __attribute__((cleanup(fun)))

#define G_PASTE_CLEANUP_FREE          G_PASTE_CLEANUP (g_paste_free_ptr)
#define G_PASTE_CLEANUP_ARRAY_FREE    G_PASTE_CLEANUP (g_paste_array_free_ptr)
#define G_PASTE_CLEANUP_B_STRV_FREE   G_PASTE_CLEANUP (g_paste_b_strv_free_ptr)
#define G_PASTE_CLEANUP_ERROR_FREE    G_PASTE_CLEANUP (g_paste_error_free_ptr)
#define G_PASTE_CLEANUP_SELECT_FREE   G_PASTE_CLEANUP (g_paste_select_free_ptr)
#define G_PASTE_CLEANUP_STRING_FREE   G_PASTE_CLEANUP (g_paste_string_free_ptr)
#define G_PASTE_CLEANUP_STRFREEV      G_PASTE_CLEANUP (g_paste_strfreev_ptr)
#define G_PASTE_CLEANUP_VT_FREE       G_PASTE_CLEANUP (g_paste_vt_free_ptr)
#define G_PASTE_CLEANUP_UNREF         G_PASTE_CLEANUP (g_paste_unref_ptr)
#define G_PASTE_CLEANUP_DATE_UNREF    G_PASTE_CLEANUP (g_paste_date_unref_ptr)
#define G_PASTE_CLEANUP_LOOP_UNREF    G_PASTE_CLEANUP (g_paste_loop_unref_ptr)
#define G_PASTE_CLEANUP_REGEX_UNREF   G_PASTE_CLEANUP (g_paste_regex_unref_ptr)
#define G_PASTE_CLEANUP_TARGETS_UNREF G_PASTE_CLEANUP (g_paste_targets_unref_ptr)
#define G_PASTE_CLEANUP_VARIANT_UNREF G_PASTE_CLEANUP (g_paste_variant_unref_ptr)

#define G_PASTE_TRIVIAL_CLEANUP_FUN(name, type, fun) \
    static inline void                               \
    g_paste_##name##_ptr (gpointer ptr)              \
    {                                                \
        type *_ptr = ptr;                            \
        if (*_ptr)                                   \
            fun (*_ptr);                             \
    }

#define G_PASTE_CLEANUP_FUN_WITH_ARG(name, type, fun, arg) \
    static inline void                                     \
    g_paste_##name##_ptr (type *ptr)                       \
    {                                                      \
        if (*ptr)                                          \
            fun (*ptr, arg);                               \
    }

static inline void
g_paste_free_ptr (gpointer ptr)
{
    g_free (*((gpointer *) ptr));
}

static inline void
g_paste_unref_ptr (gpointer ptr)
{
    GObject **object = ptr;
    if (*object)
        g_object_unref (*object);
}

#define G_PASTE_BOXED_FREE_REV(box, type) g_boxed_free (type, box)

G_PASTE_TRIVIAL_CLEANUP_FUN  (error_free,    GError *,           g_error_free)
G_PASTE_TRIVIAL_CLEANUP_FUN  (select_free,   GtkSelectionData *, gtk_selection_data_free)
G_PASTE_TRIVIAL_CLEANUP_FUN  (strfreev,      GStrv,              g_strfreev)
G_PASTE_TRIVIAL_CLEANUP_FUN  (vt_free,       GVariantType *,     g_variant_type_free)
G_PASTE_TRIVIAL_CLEANUP_FUN  (date_unref,    GDateTime *,        g_date_time_unref)
G_PASTE_TRIVIAL_CLEANUP_FUN  (loop_unref,    GMainLoop *,        g_main_loop_unref)
G_PASTE_TRIVIAL_CLEANUP_FUN  (regex_unref,   GRegex *,           g_regex_unref)
G_PASTE_TRIVIAL_CLEANUP_FUN  (targets_unref, GtkTargetList *,    gtk_target_list_unref)
G_PASTE_TRIVIAL_CLEANUP_FUN  (variant_unref, GVariant *,         g_variant_unref)

G_PASTE_CLEANUP_FUN_WITH_ARG (array_free,    GArray *,           g_array_free,           FALSE)
G_PASTE_CLEANUP_FUN_WITH_ARG (b_strv_free,   GStrv,              G_PASTE_BOXED_FREE_REV, G_TYPE_STRV)
G_PASTE_CLEANUP_FUN_WITH_ARG (string_free,   GString *,          g_string_free,          TRUE)

G_END_DECLS

#endif /*__GPASTE_MACROS_H__*/
