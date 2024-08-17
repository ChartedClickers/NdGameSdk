// https://gist.github.com/thwarted/8ce47e1897a578f4e80a

/* all this verbosity is required for this to work reliably and predictably
 * on both GCC and MSVC
 */

 /* because gcc cpp doesn't recursively expand macros, so a single CALLIT
  * macro can't be used in all the FE_n macros below
  */
#define FE_CALLITn01(a,b)  a b
#define FE_CALLITn02(a,b)  a b
#define FE_CALLITn03(a,b)  a b 
#define FE_CALLITn04(a,b)  a b
#define FE_CALLITn04(a,b)  a b
#define FE_CALLITn05(a,b)  a b
#define FE_CALLITn06(a,b)  a b
#define FE_CALLITn07(a,b)  a b
#define FE_CALLITn08(a,b)  a b
#define FE_CALLITn09(a,b)  a b
#define FE_CALLITn10(a,b)  a b
#define FE_CALLITn11(a,b)  a b
#define FE_CALLITn12(a,b)  a b
#define FE_CALLITn13(a,b)  a b
#define FE_CALLITn14(a,b)  a b
#define FE_CALLITn15(a,b)  a b
#define FE_CALLITn16(a,b)  a b
#define FE_CALLITn17(a,b)  a b
#define FE_CALLITn18(a,b)  a b
#define FE_CALLITn19(a,b)  a b
#define FE_CALLITn20(a,b)  a b
#define FE_CALLITn21(a,b)  a b

  /* the MSVC preprocessor expands __VA_ARGS__ as a single argument, so it needs
   * to be expanded indirectly through the CALLIT macros.
   * http://connect.microsoft.com/VisualStudio/feedback/details/380090/variadic-macro-replacement
   * http://stackoverflow.com/questions/21869917/visual-studio-va-args-issue
   */
   
#define FE_n00()
#define FE_n01(what, a, ...)  what(a)
#define FE_n02(what, a, ...)  what(a) FE_CALLITn02(FE_n01,(what, ##__VA_ARGS__))
#define FE_n03(what, a, ...)  what(a) FE_CALLITn03(FE_n02,(what, ##__VA_ARGS__))
#define FE_n04(what, a, ...)  what(a) FE_CALLITn04(FE_n03,(what, ##__VA_ARGS__))
#define FE_n05(what, a, ...)  what(a) FE_CALLITn05(FE_n04,(what, ##__VA_ARGS__))
#define FE_n06(what, a, ...)  what(a) FE_CALLITn06(FE_n05,(what, ##__VA_ARGS__))
#define FE_n07(what, a, ...)  what(a) FE_CALLITn07(FE_n06,(what, ##__VA_ARGS__))
#define FE_n08(what, a, ...)  what(a) FE_CALLITn08(FE_n07,(what, ##__VA_ARGS__))
#define FE_n09(what, a, ...)  what(a) FE_CALLITn09(FE_n08,(what, ##__VA_ARGS__))
#define FE_n10(what, a, ...)  what(a) FE_CALLITn10(FE_n09,(what, ##__VA_ARGS__))
#define FE_n11(what, a, ...)  what(a) FE_CALLITn11(FE_n10,(what, ##__VA_ARGS__))
#define FE_n12(what, a, ...)  what(a) FE_CALLITn12(FE_n11,(what, ##__VA_ARGS__))
#define FE_n13(what, a, ...)  what(a) FE_CALLITn13(FE_n12,(what, ##__VA_ARGS__))
#define FE_n14(what, a, ...)  what(a) FE_CALLITn14(FE_n13,(what, ##__VA_ARGS__))
#define FE_n15(what, a, ...)  what(a) FE_CALLITn15(FE_n14,(what, ##__VA_ARGS__))
#define FE_n16(what, a, ...)  what(a) FE_CALLITn16(FE_n15,(what, ##__VA_ARGS__))
#define FE_n17(what, a, ...)  what(a) FE_CALLITn17(FE_n16,(what, ##__VA_ARGS__))
#define FE_n18(what, a, ...)  what(a) FE_CALLITn18(FE_n17,(what, ##__VA_ARGS__))
#define FE_n19(what, a, ...)  what(a) FE_CALLITn19(FE_n18,(what, ##__VA_ARGS__))
#define FE_n20(what, a, ...)  what(a) FE_CALLITn20(FE_n19,(what, ##__VA_ARGS__))
#define FE_n21(what, a, ...)  what(a) FE_CALLITn21(FE_n20,(what, ##__VA_ARGS__))
#define FE_n22(...)           ERROR: FOR_EACH only supports up to 21 arguments

#define FE_GET_MACRO(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,NAME,...) NAME
#define FOR_EACH(what, ...) FE_CALLITn01(FE_GET_MACRO(_0, ##__VA_ARGS__,FE_n22,FE_n21,FE_n20,FE_n19, \
                            FE_n18,FE_n17,FE_n16,FE_n15,FE_n14,FE_n13,FE_n12,FE_n11,FE_n10,FE_n09,\
                            FE_n08,FE_n07,FE_n06,FE_n05,FE_n04,FE_n03,FE_n02,FE_n01,FE_n00), (what, ##__VA_ARGS__))