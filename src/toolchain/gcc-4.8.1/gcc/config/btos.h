/* Useful if you wish to make target-specific gcc changes. */
#undef TARGET_BTOS
#define TARGET_BTOS 1

/* Don't automatically add extern "C" { } around header files.  */
#undef  NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C 1

/* Additional predefined macros. */
#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()      \
  do {                                \
    builtin_define ("__btos__");      \
    builtin_define ("__unix__");      \
    builtin_assert ("system=btos");   \
    builtin_assert ("system=unix");   \
    builtin_assert ("system=posix");   \
  } while(0);

#undef STARTFILE_SPEC
#define STARTFILE_SPEC "%{!shared: %{!pg:crt0.o%s}} crti.o%s crtbegin.o%s"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn.o%s"

#undef LINK_SPEC
#define LINK_SPEC "\
  %{shared:-shared} \
  %{!shared: \
    %{!static: \
      %{rdynamic:-export-dynamic} \
      -dynamic-linker ELOADER.ELX} \
      %{static:-static}}"
      
#undef LINK_EH_SPEC
#define LINK_EH_SPEC ""
