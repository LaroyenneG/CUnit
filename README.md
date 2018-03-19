# CUnit


Example of use :
```c
/*
  Test fonction
*/
void test1() {
  ASSERT_TRUE(1==2);
}


int main(void) {

  CUNIT_ADD_TEST_FUNCTION(&test1,"test 1");
  
  CUNIT_RUN();

  return 0;
}

```
