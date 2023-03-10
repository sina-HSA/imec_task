
AC_DEFUN([SST_CHECK_SHM], [

  sst_check_shm_happy="yes"

  AC_LANG_PUSH(C)
  AC_SEARCH_LIBS([shm_open], [rt], [SHM_LIB="$LIBS"], [sst_check_shm_happy="no"])
  AC_LANG_POP(C)

  AC_SUBST([SHM_LIB])
  AM_CONDITIONAL([HAVE_SHM], [test "$sst_check_shm_happy" = "yes"])
  AS_IF([test "$sst_check_shm_happy" = "yes"],
        [AC_DEFINE([HAVE_SHM], [1], [Set to 1 if SHM was found])])

  AS_IF([test "$sst_check_shm_happy" = "yes"], [$1], [$2])
])
