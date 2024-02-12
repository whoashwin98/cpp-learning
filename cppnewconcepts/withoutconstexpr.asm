@REM  if the value is being computed at run-time, like in this case we are generating a random number using std::random
@REM then we have no other choice but to make the computations during run-time.
 
 call   31 <main+0x31>
    R_X86_64_PLT32 std::random_device::operator()()-0x4
 mov    %eax,-0x13a8(%rbp)
 jmp    3c <main+0x3c>
 mov    -0x13a8(%rbp),%edi
 mov    %edi,%eax
 mov    $0xaaaaaaab,%ecx
 imul   %rcx,%rax
 shr    $0x22,%rax
 mov    %eax,%ecx
 add    %ecx,%ecx
 mov    %ecx,%eax
 lea    (%rax,%rax,2),%eax
 sub    %eax,%edi
 call   61 <main+0x61>
    R_X86_64_PLT32 factorial(int)-0x4
 mov    %eax,-0x13b4(%rbp)
 jmp    6c <main+0x6c>
 mov    -0x13b4(%rbp),%eax
 mov    %eax,-0x1394(%rbp)