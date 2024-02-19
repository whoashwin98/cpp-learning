// case 1: s_var in both files is non-static, leads to linking error as it treats them as duplicate
// int s_var = 123;

// case 2: s_var is static here
// when we use the static keyword here, it means this variable is now limited to only this source file
static int s_var = 123;

// case 3: s_var is non-static here, and extern in Main file
// int s_var = 123;