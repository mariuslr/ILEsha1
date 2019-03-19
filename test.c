/*
SHA1 tests by Philip Woolford <woolford.philip@gmail.com>
100% Public Domain
 */

#include "sha1.h"
#include "stdio.h"
#include "string.h"

#define SUCCESS 0

void CU_ASSERT (int ok) 
{
    printf ("%s\n" , ok ? "OK":"ERROR");
}

/* Test Vector 1 */
void testvec1(
    void
)
{
#pragma convert(1252)
  char const string[] = "abc";
#pragma convert(0)

  char const expect[] = "a9993e364706816aba3e25717850c26c9cd0d89d";
  char result[21];
  char hexresult[41];
  size_t offset;

  /* calculate hash */
  SHA1( result, string, strlen(string) );

  /* format the hash for comparison */
  for( offset = 0; offset < 20; offset++) {
    sprintf( ( hexresult + (2*offset)), "%02x", result[offset]&0xff);
  }

  CU_ASSERT( strncmp(hexresult, expect, 40) == SUCCESS );
}

/* Test Vector 2 */
void testvec2(
    void
)
{
#pragma convert(1252)
  char const string[] = "";
#pragma convert(0)

  char const expect[] = "da39a3ee5e6b4b0d3255bfef95601890afd80709";
  char result[21];
  char hexresult[41];
  size_t offset;

  /* calculate hash */
  SHA1( result, string, strlen(string) );

  /*format the hash for comparison */
  for( offset = 0; offset < 20; offset++) {
    sprintf( ( hexresult + (2*offset)), "%02x", result[offset]&0xff);
  }

  CU_ASSERT( strncmp(hexresult, expect, 40) == SUCCESS );
}

/* Test Vector 3 */
void testvec3(
    void
)
{
#pragma convert(1252)
  char const string[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
#pragma convert(0)

  char const expect[] = "84983e441c3bd26ebaae4aa1f95129e5e54670f1";
  char result[21];
  char hexresult[41];
  size_t offset;

  /* calculate hash */
  SHA1( result, string, strlen(string) );

  /* format the hash for comparison */
  for( offset = 0; offset < 20; offset++) {
    sprintf( ( hexresult + (2*offset)), "%02x", result[offset]&0xff);
  }

  CU_ASSERT( strncmp(hexresult, expect, 40) == SUCCESS );
}

/* Test Vector 4 */
void testvec4(
    void
)
{
#pragma convert(1252)
  char const string1[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghij";
  char const string2[] = "klmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
#pragma convert(0)
  char const expect[] = "a49b2446a02c645bf419f995b67091253a04a259";
  unsigned char result[21];
  char hexresult[41];
  size_t offset;
  SHA1_CTX ctx;

  /* calculate hash */
  SHA1Init(&ctx);
  SHA1Update( &ctx, (unsigned char const *)string1, strlen(string1) );
  SHA1Update( &ctx, (unsigned char const *)string2, strlen(string2) );
  SHA1Final(result, &ctx);

  /* format the hash for comparison */
  for( offset = 0; offset < 20; offset++) {
    sprintf( ( hexresult + (2*offset)), "%02x", result[offset]&0xff);
  }

  CU_ASSERT( strncmp(hexresult, expect, 40) == SUCCESS );
}

/* Test Vector 5 */
void testvec5(
    void
)
{

  char string[1000001];
  char const expect[] = "34aa973cd4c4daa4f61eeb2bdbad27316534016f";
  char result[21];
  char hexresult[41];
  int iterator;
  size_t offset;

  /* generate string */
#pragma convert(1252)

  for( iterator = 0; iterator < 1000000; iterator++) {
    string[iterator] = 'a';
  }
  string[1000000] = '\0';
#pragma convert(0)

  /* calculate hash */
  SHA1( result, string, strlen(string) );

  /* format the hash for comparison */
  for( offset = 0; offset < 20; offset++) {
    sprintf( ( hexresult + (2*offset)), "%02x", result[offset]&0xff);
  }

  CU_ASSERT( strncmp(hexresult, expect, 40) == SUCCESS );
}

/* Test Vector 6 */
void testvec6(
    void
)
{
#pragma convert(1252)
  char const string[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno";
#pragma convert(0)
  char const expect[] = "7789f0c9ef7bfc40d93311143dfbe69e2017f592";
  unsigned char result[21];
  char hexresult[41];
  int iterator;
  size_t offset;
  SHA1_CTX ctx;

  /* calculate hash */
  SHA1Init(&ctx);
  for ( iterator = 0; iterator < 16777216; iterator++) {
    SHA1Update( &ctx, (unsigned char const *)string, strlen(string) );
  }
  SHA1Final(result, &ctx);

  /* format the hash for comparison */
  for( offset = 0; offset < 20; offset++) {
    sprintf( ( hexresult + (2*offset)), "%02x", result[offset]&0xff);
  }

  CU_ASSERT( strncmp(hexresult, expect, 40) == SUCCESS );
}

int main(void)
{
  testvec1();
  testvec2();
  testvec3();
  testvec4();
  testvec5();
  testvec6();
 }
