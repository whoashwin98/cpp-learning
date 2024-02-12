@REM  it is clearly visible that, since the value 7 was already known during compile time, we can save some runtime
@REM overhead by making the factorial function constexpr and the storing result constexpr as well
@REM this enables the compiler to perform this calculation at compile time 
 
 movl   $0x13b0,-0x8(%rbp)