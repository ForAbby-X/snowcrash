void test(void)
{
	const char test[2] = ".\n";
	write(1, test, 2);
}
/*
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 28             	sub    $0x28,%esp
   6:	a1 00 00 00 00       	mov    0x0,%eax
   b:	89 45 f1             	mov    %eax,-0xf(%ebp)
   e:	a1 04 00 00 00       	mov    0x4,%eax
  13:	89 45 f5             	mov    %eax,-0xb(%ebp)
  16:	a1 08 00 00 00       	mov    0x8,%eax
  1b:	89 45 f9             	mov    %eax,-0x7(%ebp)
  1e:	66 a1 0c 00 00 00    	mov    0xc,%ax
  24:	66 89 45 fd          	mov    %ax,-0x3(%ebp)
  28:	a0 0e 00 00 00       	mov    0xe,%al
  2d:	88 45 ff             	mov    %al,-0x1(%ebp)
  30:	8d 45 f1             	lea    -0xf(%ebp),%eax
  33:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
  3a:	89 44 24 04          	mov    %eax,0x4(%esp)
  3e:	c7 44 24 08 0e 00 00 	movl   $0xe,0x8(%esp)
  45:	00 
  46:	e8 fc ff ff ff       	call   47 <test+0x47>
  4b:	83 c4 28             	add    $0x28,%esp
  4e:	5d                   	pop    %ebp
  4f:	c3                   	ret 

\x55\x89\xe5\x83\xec\x28\xa1\x00\x00\x00\x00\x89\x45\xf1\xa1\x04\x00\x00\x00\x89\x45\xf5\xa1\x08\x00\x00\x00\x89\x45\xf9\x66\xa1\x0c\x00\x00\x00\x66\x89\x45\xfd\xa0\x0e\x00\x00\x00\x88\x45\xff\x8d\x45\xf1\xc7\x04\x24\x01\x00\x00\x00\x89\x44\x24\x04\xc7\x44\x24\x08\x0e\x00\x00\x00\xe8\xfc\xff\xff\xff\x83\xc4\x28\x5d\xc3
*/