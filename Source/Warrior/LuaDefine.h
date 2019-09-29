#pragma once
#define MAXARGNUM 10 //最多10个参数，不包含类实例
#define REPEAT_0(m, ...) 
#define REPEAT_1(m, ...)  m(1, __VA_ARGS__)
#define REPEAT_2(m, ...)  REPEAT_1(m, __VA_ARGS__),  m(2, __VA_ARGS__)
#define REPEAT_3(m, ...)  REPEAT_2(m, __VA_ARGS__),  m(3, __VA_ARGS__)
#define REPEAT_4(m, ...)  REPEAT_3(m, __VA_ARGS__),  m(4, __VA_ARGS__)
#define REPEAT_5(m, ...)  REPEAT_4(m, __VA_ARGS__),  m(5, __VA_ARGS__)
#define REPEAT_6(m, ...)  REPEAT_5(m, __VA_ARGS__),  m(6, __VA_ARGS__)
#define REPEAT_7(m, ...)  REPEAT_6(m, __VA_ARGS__),  m(7, __VA_ARGS__)
#define REPEAT_8(m, ...)  REPEAT_7(m, __VA_ARGS__),  m(8, __VA_ARGS__)
#define REPEAT_9(m, ...)  REPEAT_8(m, __VA_ARGS__),  m(9, __VA_ARGS__)
#define REPEAT_10(m, ...) REPEAT_9(m, __VA_ARGS__), m(10, __VA_ARGS__)
#define REPEAT_(n, m, ...) REPEAT_##n(m, __VA_ARGS__)

#define IF_0(f1, f2, a1,a2) f2( a1,a2 )
#define IF_1(f1, f2, a1,a2) f1( a1,a2 )
#define IF_2(f1, f2, a1,a2) f1( a1,a2 )
#define IF_3(f1, f2, a1,a2) f1( a1,a2 )
#define IF_4(f1, f2, a1,a2) f1( a1,a2 )
#define IF_5(f1, f2, a1,a2) f1( a1,a2 )
#define IF_6(f1, f2, a1,a2) f1( a1,a2 )
#define IF_7(f1, f2, a1,a2) f1( a1,a2 )
#define IF_8(f1, f2, a1,a2) f1( a1,a2 )
#define IF_9(f1, f2, a1,a2) f1( a1,a2 )
#define IF_10(f1, f2, a1,a2) f1( a1,a2 )
#define IF_(n,f1,f2,a1,a2) IF_##n(f1, f2, a1,a2)

#define R(n,f) Read<T##n>(L,(n+f))
#define W(n, ...) Write<T##n>(L,t##n)
#define PT(n, ...) T##n
#define TT(n, ...) T##n t##n
#define PTN(n, ...) typename T##n
#define PTND(n, ...) typename T##n=void


#define RN(n, f) REPEAT_(n, R, f)
#define WN(n) REPEAT_(n, W)
#define TN(n) REPEAT_(n, PT)
//typename T1, typename T2
#define TNN(n) REPEAT_(n, PTN)
#define TNND(n) REPEAT_(n, PTND)
#define TTN(n) REPEAT_(n, TT)

#define TNH0(h,n) h
#define TNH1(h,n) h, TN(n)
#define TNH(h,n) IF_(n, TNH1, TNH0, h, n) // T, T1

#define TNNH0(h, n) typename h
#define TNNH1(h, n) typename h, TNN(n)
#define TNNH(h, n) IF_(n, TNNH1, TNNH0, h, n) // typename T, typename T1

#define TNNHD0(h, n) typename h
#define TNNHD1(h, n) typename h, TNND(n)
#define TNNHD(h, n) IF_(n, TNNHD1, TNNHD0, h, n) // typename T, typename T1=void

#define VTNH(h, n) <V, TNH(h, n) >// <V, T, T1>
#define MVTNH(h, n)

#define VTN(h, n) <TNH(h, n)>// <V, T1>
#define MVTN(h, n)

#define NTN(n) <TN(n)>// <V, T1>
#define MTN(n)
