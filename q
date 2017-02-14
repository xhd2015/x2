
main.bimg：     文件格式 binary


Disassembly of section .data:

00000000 <.data>:
       0:	ea 05 00 c0 07 fa b8 	ljmp   $0xb8fa,$0x7c00005
       7:	c0 07 8e             	rolb   $0x8e,(%edi)
       a:	d8 8e d0 8e c0 bc    	fmuls  -0x433f7130(%esi)
      10:	00 04 66             	add    %al,(%esi,%eiz,2)
      13:	e8 08 00 00 00       	call   0x20
      18:	66 e8 e2 03          	callw  0x3fe
      1c:	00 00                	add    %al,(%eax)
      1e:	eb fe                	jmp    0x1e
      20:	66 55                	push   %bp
      22:	66 89 e5             	mov    %sp,%bp
      25:	06                   	push   %es
      26:	b8 c0 07 8e c0       	mov    $0xc08e07c0,%eax
      2b:	bb 00 04 31 d2       	mov    $0xd2310400,%ebx
      30:	b9 03 00 b8 0e       	mov    $0xeb80003,%ecx
      35:	02 cd                	add    %ch,%cl
      37:	13 07                	adc    (%edi),%eax
      39:	90                   	nop
      3a:	66 5d                	pop    %bp
      3c:	66 c3                	retw   
      3e:	90                   	nop
      3f:	90                   	nop
      40:	48                   	dec    %eax
      41:	65 6c                	gs insb (%dx),%es:(%edi)
      43:	6c                   	insb   (%dx),%es:(%edi)
      44:	6f                   	outsl  %ds:(%esi),(%dx)
      45:	20 57 6f             	and    %dl,0x6f(%edi)
      48:	72 6c                	jb     0xb6
      4a:	64 21 00             	and    %eax,%fs:(%eax)
      4d:	4c                   	dec    %esp
      4e:	6f                   	outsl  %ds:(%esi),(%dx)
      4f:	61                   	popa   
      50:	64 20 54 65 73       	and    %dl,%fs:0x73(%ebp,%eiz,2)
      55:	74 65                	je     0xbc
      57:	64 2e 0a 00          	fs or  %cs:(%eax),%al
      5b:	53                   	push   %ebx
      5c:	65 67 6d             	gs insl (%dx),%es:(%di)
      5f:	65 6e                	outsb  %gs:(%esi),(%dx)
      61:	74 44                	je     0xa7
      63:	65 73 63             	gs jae 0xc9
      66:	72 69                	jb     0xd1
      68:	70 74                	jo     0xde
      6a:	6f                   	outsl  %ds:(%esi),(%dx)
      6b:	72 20                	jb     0x8d
      6d:	52                   	push   %edx
      6e:	69 67 68 74 21 21 21 	imul   $0x21212174,0x68(%edi),%esp
      75:	0a 00                	or     (%eax),%al
      77:	55                   	push   %ebp
      78:	74 69                	je     0xe3
      7a:	6c                   	insb   (%dx),%es:(%edi)
      7b:	20 54 68 65          	and    %dl,0x65(%eax,%ebp,2)
      7f:	20 45 6e             	and    %al,0x6e(%ebp)
      82:	64 2e 0a 00          	fs or  %cs:(%eax),%al
	...
     1fe:	55                   	push   %ebp
     1ff:	aa                   	stos   %al,%es:(%edi)
	...
     400:	66 55                	push   %bp
     402:	66 89 e5             	mov    %sp,%bp
     405:	66 83 ec 78          	sub    $0x78,%sp
     409:	66 a1 48 1d 67 66    	mov    0x66671d48,%ax
     40f:	89 44 24 04          	mov    %eax,0x4(%esp)
     413:	67 66 c7 04 24 40    	movw   $0x4024,(%si)
     419:	00 00                	add    %al,(%eax)
     41b:	00 66 e8             	add    %ah,-0x18(%esi)
     41e:	a4                   	movsb  %ds:(%esi),%es:(%edi)
     41f:	03 00                	add    (%eax),%eax
     421:	00 67 66             	add    %ah,0x66(%edi)
     424:	8d 45 f7             	lea    -0x9(%ebp),%eax
     427:	66 89 c1             	mov    %ax,%cx
     42a:	66 e8 00 03          	callw  0x72e
     42e:	00 00                	add    %al,(%eax)
     430:	67 66 8d 45 f7       	lea    -0x9(%di),%ax
     435:	66 89 c1             	mov    %ax,%cx
     438:	66 e8 56 03          	callw  0x792
     43c:	00 00                	add    %al,(%eax)
     43e:	67 66 c7 44 24 10 00 	movw   $0x10,0x24(%si)
     445:	02 00                	add    (%eax),%al
     447:	00 67 66             	add    %ah,0x66(%edi)
     44a:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
     451:	00 
     452:	67 66 c7 44 24 08 c0 	movw   $0xc008,0x24(%si)
     459:	07                   	pop    %es
     45a:	00 00                	add    %al,(%eax)
     45c:	67 66 c7 44 24 04 00 	movw   $0x4,0x24(%si)
     463:	02 00                	add    (%eax),%al
     465:	00 67 66             	add    %ah,0x66(%edi)
     468:	c7 04 24 c0 07 00 00 	movl   $0x7c0,(%esp)
     46f:	66 e8 a1 05          	callw  0xa14
     473:	00 00                	add    %al,(%eax)
     475:	67 66 c7 44 24 10 01 	movw   $0x110,0x24(%si)
     47c:	00 00                	add    %al,(%eax)
     47e:	00 67 66             	add    %ah,0x66(%edi)
     481:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
     488:	00 
     489:	67 66 c7 44 24 08 00 	movw   $0x8,0x24(%si)
     490:	00 00                	add    %al,(%eax)
     492:	00 67 66             	add    %ah,0x66(%edi)
     495:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
     49c:	00 
     49d:	67 66 c7 04 24 c0    	movw   $0xc024,(%si)
     4a3:	07                   	pop    %es
     4a4:	00 00                	add    %al,(%eax)
     4a6:	66 e8 80 07          	callw  0xc2a
     4aa:	00 00                	add    %al,(%eax)
     4ac:	66 85 c0             	test   %ax,%ax
     4af:	0f 95 c0             	setne  %al
     4b2:	84 c0                	test   %al,%al
     4b4:	74 19                	je     0x4cf
     4b6:	66 a1 48 1d 67 66    	mov    0x66671d48,%ax
     4bc:	89 44 24 04          	mov    %eax,0x4(%esp)
     4c0:	67 66 c7 04 24 4d    	movw   $0x4d24,(%si)
     4c6:	00 00                	add    %al,(%eax)
     4c8:	00 66 e8             	add    %ah,-0x18(%esi)
     4cb:	f7 02 00 00 66 a1    	testl  $0xa1660000,(%edx)
     4d1:	c0 1d 66 0f be c8 66 	rcrb   $0x66,0xc8be0f66
     4d8:	a1 78 1d 66 0f       	mov    0xf661d78,%eax
     4dd:	be d0 67 66 8d       	mov    $0x8d6667d0,%esi
     4e2:	45                   	inc    %ebp
     4e3:	e8 67 66 c7 44       	call   0x44c76b4f
     4e8:	24 18                	and    $0x18,%al
     4ea:	01 00                	add    %eax,(%eax)
     4ec:	00 00                	add    %al,(%eax)
     4ee:	67 66 c7 44 24 14 01 	movw   $0x114,0x24(%si)
     4f5:	00 00                	add    %al,(%eax)
     4f7:	00 67 66             	add    %ah,0x66(%edi)
     4fa:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
     501:	00 
     502:	67 66 89 4c 24       	mov    %cx,0x24(%si)
     507:	0c 67                	or     $0x67,%al
     509:	66 89 54 24 08       	mov    %dx,0x8(%esp)
     50e:	67 66 c7 44 24 04 00 	movw   $0x4,0x24(%si)
     515:	04 00                	add    $0x0,%al
     517:	00 67 66             	add    %ah,0x66(%edi)
     51a:	c7 04 24 00 7c 00 00 	movl   $0x7c00,(%esp)
     521:	66 89 c1             	mov    %ax,%cx
     524:	66 e8 bc 0e          	callw  0x13e4
     528:	00 00                	add    %al,(%eax)
     52a:	66 83 ec 1c          	sub    $0x1c,%sp
     52e:	67 66 8d 45 e8       	lea    -0x18(%di),%ax
     533:	67 66 8d 55 e0       	lea    -0x20(%di),%dx
     538:	67 66 89 54 24       	mov    %dx,0x24(%si)
     53d:	04 67                	add    $0x67,%al
     53f:	66 c7 04 24 00 00    	movw   $0x0,(%esp)
     545:	01 00                	add    %eax,(%eax)
     547:	66 89 c1             	mov    %ax,%cx
     54a:	66 e8 de 10          	callw  0x162c
     54e:	00 00                	add    %al,(%eax)
     550:	66 83 ec 08          	sub    $0x8,%sp
     554:	66 a1 c0 1d 66 0f    	mov    0xf661dc0,%ax
     55a:	be c8 66 a1 78       	mov    $0x78a166c8,%esi
     55f:	1d 66 0f be d0       	sbb    $0xd0be0f66,%eax
     564:	67 66 8d 45 d1       	lea    -0x2f(%di),%ax
     569:	67 66 c7 44 24 18 01 	movw   $0x118,0x24(%si)
     570:	00 00                	add    %al,(%eax)
     572:	00 67 66             	add    %ah,0x66(%edi)
     575:	c7 44 24 14 01 00 00 	movl   $0x1,0x14(%esp)
     57c:	00 
     57d:	67 66 c7 44 24 10 01 	movw   $0x110,0x24(%si)
     584:	00 00                	add    %al,(%eax)
     586:	00 67 66             	add    %ah,0x66(%edi)
     589:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
     58d:	67 66 89 54 24       	mov    %dx,0x24(%si)
     592:	08 67 66             	or     %ah,0x66(%edi)
     595:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
     59c:	00 
     59d:	67 66 c7 04 24 00    	movw   $0x24,(%si)
     5a3:	00 00                	add    %al,(%eax)
     5a5:	00 66 89             	add    %ah,-0x77(%esi)
     5a8:	c1 66 e8 37          	shll   $0x37,-0x18(%esi)
     5ac:	0e                   	push   %cs
     5ad:	00 00                	add    %al,(%eax)
     5af:	66 83 ec 1c          	sub    $0x1c,%sp
     5b3:	67 66 8d 45 e0       	lea    -0x20(%di),%ax
     5b8:	67 66 89 44 24       	mov    %ax,0x24(%si)
     5bd:	08 67 66             	or     %ah,0x66(%edi)
     5c0:	c7 44 24 04 00 00 01 	movl   $0x10000,0x4(%esp)
     5c7:	00 
     5c8:	67 66 8d 45 d1       	lea    -0x2f(%di),%ax
     5cd:	67 66 89 04          	mov    %ax,(%si)
     5d1:	24 66                	and    $0x66,%al
     5d3:	e8 86 12 00 00       	call   0x185e
     5d8:	67 66 8d 45 d1       	lea    -0x2f(%di),%ax
     5dd:	67 66 8d 55 c9       	lea    -0x37(%di),%dx
     5e2:	67 66 89 54 24       	mov    %dx,0x24(%si)
     5e7:	04 67                	add    $0x67,%al
     5e9:	66 c7 04 24 00 00    	movw   $0x0,(%esp)
     5ef:	01 00                	add    %eax,(%eax)
     5f1:	66 89 c1             	mov    %ax,%cx
     5f4:	66 e8 34 10          	callw  0x162c
     5f8:	00 00                	add    %al,(%eax)
     5fa:	66 83 ec 08          	sub    $0x8,%sp
     5fe:	67 66 8d 45 e8       	lea    -0x18(%di),%ax
     603:	67 66 8d 55 d1       	lea    -0x2f(%di),%dx
     608:	67 66 89 14          	mov    %dx,(%si)
     60c:	24 66                	and    $0x66,%al
     60e:	89 c1                	mov    %eax,%ecx
     610:	66 e8 da 0e          	callw  0x14ee
     614:	00 00                	add    %al,(%eax)
     616:	66 83 ec 04          	sub    $0x4,%sp
     61a:	66 85 c0             	test   %ax,%ax
     61d:	0f 95 c0             	setne  %al
     620:	84 c0                	test   %al,%al
     622:	74 19                	je     0x63d
     624:	66 a1 48 1d 67 66    	mov    0x66671d48,%ax
     62a:	89 44 24 04          	mov    %eax,0x4(%esp)
     62e:	67 66 c7 04 24 5b    	movw   $0x5b24,(%si)
     634:	00 00                	add    %al,(%eax)
     636:	00 66 e8             	add    %ah,-0x18(%esi)
     639:	89 01                	mov    %eax,(%ecx)
     63b:	00 00                	add    %al,(%eax)
     63d:	66 a1 48 1d 67 66    	mov    0x66671d48,%ax
     643:	89 44 24 04          	mov    %eax,0x4(%esp)
     647:	67 66 c7 04 24 77    	movw   $0x7724,(%si)
     64d:	00 00                	add    %al,(%eax)
     64f:	00 66 e8             	add    %ah,-0x18(%esi)
     652:	70 01                	jo     0x655
     654:	00 00                	add    %al,(%eax)
     656:	67 66 8d 45 b5       	lea    -0x4b(%di),%ax
     65b:	67 66 c7 44 24 10 00 	movw   $0x10,0x24(%si)
     662:	00 00                	add    %al,(%eax)
     664:	00 67 66             	add    %ah,0x66(%edi)
     667:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
     66e:	00 
     66f:	67 66 c7 44 24 08 22 	movw   $0x2208,0x24(%si)
     676:	00 00                	add    %al,(%eax)
     678:	00 67 66             	add    %ah,0x66(%edi)
     67b:	c7 44 24 04 10 00 00 	movl   $0x10,0x4(%esp)
     682:	00 
     683:	67 66 c7 04 24 00    	movw   $0x24,(%si)
     689:	00 00                	add    %al,(%eax)
     68b:	00 66 89             	add    %ah,-0x77(%esi)
     68e:	c1 66 e8 9f          	shll   $0x9f,-0x18(%esi)
     692:	06                   	push   %es
     693:	00 00                	add    %al,(%eax)
     695:	66 83 ec 14          	sub    $0x14,%sp
     699:	67 66 8d 45 b5       	lea    -0x4b(%di),%ax
     69e:	67 66 c7 44 24 18 00 	movw   $0x18,0x24(%si)
     6a5:	08 00                	or     %al,(%eax)
     6a7:	00 67 66             	add    %ah,0x66(%edi)
     6aa:	c7 44 24 14 ff ff 0f 	movl   $0xfffff,0x14(%esp)
     6b1:	00 
     6b2:	67 66 c7 44 24 10 00 	movw   $0x10,0x24(%si)
     6b9:	00 00                	add    %al,(%eax)
     6bb:	00 67 66             	add    %ah,0x66(%edi)
     6be:	c7 44 24 0c 20 03 00 	movl   $0x320,0xc(%esp)
     6c5:	00 
     6c6:	67 66 c7 44 24 08 90 	movw   $0x9008,0x24(%si)
     6cd:	9d                   	popf   
     6ce:	00 00                	add    %al,(%eax)
     6d0:	67 66 c7 44 24 04 90 	movw   $0x9004,0x24(%si)
     6d7:	01 00                	add    %eax,(%eax)
     6d9:	00 67 66             	add    %ah,0x66(%edi)
     6dc:	c7 04 24 00 9c 00 00 	movl   $0x9c00,(%esp)
     6e3:	66 89 c1             	mov    %ax,%cx
     6e6:	66 e8 72 08          	callw  0xf5c
     6ea:	00 00                	add    %al,(%eax)
     6ec:	66 83 ec 1c          	sub    $0x1c,%sp
     6f0:	67 66 8d 45 b5       	lea    -0x4b(%di),%ax
     6f5:	66 89 c1             	mov    %ax,%cx
     6f8:	66 e8 96 06          	callw  0xd92
     6fc:	00 00                	add    %al,(%eax)
     6fe:	67 66 8d 45 d1       	lea    -0x2f(%di),%ax
     703:	66 89 c1             	mov    %ax,%cx
     706:	66 e8 b8 0c          	callw  0x13c2
     70a:	00 00                	add    %al,(%eax)
     70c:	67 66 8d 45 e8       	lea    -0x18(%di),%ax
     711:	66 89 c1             	mov    %ax,%cx
     714:	66 e8 aa 0c          	callw  0x13c2
     718:	00 00                	add    %al,(%eax)
     71a:	67 66 8d 45 f7       	lea    -0x9(%di),%ax
     71f:	66 89 c1             	mov    %ax,%cx
     722:	66 e8 3a 00          	callw  0x760
     726:	00 00                	add    %al,(%eax)
     728:	90                   	nop
     729:	66 c9                	leavew 
     72b:	66 c3                	retw   
     72d:	90                   	nop
     72e:	90                   	nop
     72f:	90                   	nop
     730:	66 55                	push   %bp
     732:	66 89 e5             	mov    %sp,%bp
     735:	66 83 ec 28          	sub    $0x28,%sp
     739:	67 66 89 4d f4       	mov    %cx,-0xc(%di)
     73e:	67 66 c7 44 24 04 07 	movw   $0x704,0x24(%si)
     745:	00 00                	add    %al,(%eax)
     747:	00 67 66             	add    %ah,0x66(%edi)
     74a:	c7 04 24 54 1d 00 00 	movl   $0x1d54,(%esp)
     751:	66 e8 6f 00          	callw  0x7c4
     755:	00 00                	add    %al,(%eax)
     757:	66 e8 55 01          	callw  0x8b0
     75b:	00 00                	add    %al,(%eax)
     75d:	90                   	nop
     75e:	66 c9                	leavew 
     760:	66 c3                	retw   
     762:	66 55                	push   %bp
     764:	66 89 e5             	mov    %sp,%bp
     767:	66 83 ec 28          	sub    $0x28,%sp
     76b:	67 66 89 4d f4       	mov    %cx,-0xc(%di)
     770:	67 66 c7 44 24 04 07 	movw   $0x704,0x24(%si)
     777:	00 00                	add    %al,(%eax)
     779:	00 67 66             	add    %ah,0x66(%edi)
     77c:	c7 04 24 5c 1d 00 00 	movl   $0x1d5c,(%esp)
     783:	66 e8 3d 00          	callw  0x7c4
     787:	00 00                	add    %al,(%eax)
     789:	66 e8 23 01          	callw  0x8b0
     78d:	00 00                	add    %al,(%eax)
     78f:	90                   	nop
     790:	66 c9                	leavew 
     792:	66 c3                	retw   
     794:	66 55                	push   %bp
     796:	66 89 e5             	mov    %sp,%bp
     799:	66 83 ec 28          	sub    $0x28,%sp
     79d:	67 66 89 4d f4       	mov    %cx,-0xc(%di)
     7a2:	67 66 c7 44 24 04 07 	movw   $0x704,0x24(%si)
     7a9:	00 00                	add    %al,(%eax)
     7ab:	00 67 66             	add    %ah,0x66(%edi)
     7ae:	c7 04 24 67 1d 00 00 	movl   $0x1d67,(%esp)
     7b5:	66 e8 0b 00          	callw  0x7c4
     7b9:	00 00                	add    %al,(%eax)
     7bb:	66 e8 f1 00          	callw  0x8b0
     7bf:	00 00                	add    %al,(%eax)
     7c1:	90                   	nop
     7c2:	66 c9                	leavew 
     7c4:	66 c3                	retw   
     7c6:	66 55                	push   %bp
     7c8:	66 89 e5             	mov    %sp,%bp
     7cb:	66 83 ec 18          	sub    $0x18,%sp
     7cf:	67 66 8b 45 08       	mov    0x8(%di),%ax
     7d4:	67 66 0f b6 00       	movzbw (%bx,%si),%ax
     7d9:	84 c0                	test   %al,%al
     7db:	74 30                	je     0x80d
     7dd:	67 66 8b 45 08       	mov    0x8(%di),%ax
     7e2:	67 66 8d 50 01       	lea    0x1(%bx,%si),%dx
     7e7:	67 66 89 55 08       	mov    %dx,0x8(%di)
     7ec:	67 66 0f b6 00       	movzbw (%bx,%si),%ax
     7f1:	66 0f be c0          	movsbw %al,%ax
     7f5:	67 66 8b 55 0c       	mov    0xc(%di),%dx
     7fa:	67 66 89 54 24       	mov    %dx,0x24(%si)
     7ff:	04 67                	add    $0x67,%al
     801:	66 89 04 24          	mov    %ax,(%esp)
     805:	66 e8 07 00          	callw  0x810
     809:	00 00                	add    %al,(%eax)
     80b:	eb c2                	jmp    0x7cf
     80d:	90                   	nop
     80e:	66 c9                	leavew 
     810:	66 c3                	retw   
     812:	66 55                	push   %bp
     814:	66 89 e5             	mov    %sp,%bp
     817:	66 53                	push   %bx
     819:	66 83 ec 24          	sub    $0x24,%sp
     81d:	67 66 8b 45 08       	mov    0x8(%di),%ax
     822:	67 88 45 e4          	mov    %al,-0x1c(%di)
     826:	67 80 7d e4 0a       	cmpb   $0xa,-0x1c(%di)
     82b:	75 08                	jne    0x835
     82d:	66 e8 7f 00          	callw  0x8b0
     831:	00 00                	add    %al,(%eax)
     833:	eb 73                	jmp    0x8a8
     835:	67 80 7d e4 0d       	cmpb   $0xd,-0x1c(%di)
     83a:	75 0b                	jne    0x847
     83c:	66 c7 06 d4 1d       	movw   $0x1dd4,(%esi)
     841:	00 00                	add    %al,(%eax)
     843:	00 00                	add    %al,(%eax)
     845:	eb 61                	jmp    0x8a8
     847:	66 a1 d4 1d 66 3d    	mov    0x3d661dd4,%ax
     84d:	a0 00 00 00 75       	mov    0x75000000,%al
     852:	06                   	push   %es
     853:	66 e8 59 00          	callw  0x8b0
     857:	00 00                	add    %al,(%eax)
     859:	66 8b 16             	mov    (%esi),%dx
     85c:	d0 1d 66 89 d0 66    	rcrb   0x66d08966
     862:	c1 e0 02             	shl    $0x2,%eax
     865:	66 01 d0             	add    %dx,%ax
     868:	66 c1 e0 05          	shl    $0x5,%ax
     86c:	66 89 c2             	mov    %ax,%dx
     86f:	66 a1 d4 1d 66 01    	mov    0x1661dd4,%ax
     875:	d0 67 66             	shlb   0x66(%edi)
     878:	89 45 f4             	mov    %eax,-0xc(%ebp)
     87b:	66 8b 16             	mov    (%esi),%dx
     87e:	fc                   	cld    
     87f:	1c 67                	sbb    $0x67,%al
     881:	66 0f b6 45 e4       	movzbw -0x1c(%ebp),%ax
     886:	67 66 8b 5d f4       	mov    -0xc(%di),%bx
     88b:	67 66 8b 4d 0c       	mov    0xc(%di),%cx
     890:	06                   	push   %es
     891:	8e c2                	mov    %edx,%es
     893:	26 88 07             	mov    %al,%es:(%edi)
     896:	66 43                	inc    %bx
     898:	26 88 0f             	mov    %cl,%es:(%edi)
     89b:	07                   	pop    %es
     89c:	66 a1 d4 1d 66 83    	mov    0x83661dd4,%ax
     8a2:	c0 02 66             	rolb   $0x66,(%edx)
     8a5:	a3 d4 1d 66 83       	mov    %eax,0x83661dd4
     8aa:	c4 24 66             	les    (%esi,%eiz,2),%esp
     8ad:	5b                   	pop    %ebx
     8ae:	66 5d                	pop    %bp
     8b0:	66 c3                	retw   
     8b2:	66 55                	push   %bp
     8b4:	66 89 e5             	mov    %sp,%bp
     8b7:	66 c7 06 d4 1d       	movw   $0x1dd4,(%esi)
     8bc:	00 00                	add    %al,(%eax)
     8be:	00 00                	add    %al,(%eax)
     8c0:	66 a1 d0 1d 67 66    	mov    0x66671dd0,%ax
     8c6:	8d 48 01             	lea    0x1(%eax),%ecx
     8c9:	66 ba 1f 85          	mov    $0x851f,%dx
     8cd:	eb 51                	jmp    0x920
     8cf:	66 89 c8             	mov    %cx,%ax
     8d2:	66 f7 ea             	imul   %dx
     8d5:	66 c1 fa 03          	sar    $0x3,%dx
     8d9:	66 89 c8             	mov    %cx,%ax
     8dc:	66 c1 f8 1f          	sar    $0x1f,%ax
     8e0:	66 29 c2             	sub    %ax,%dx
     8e3:	66 89 d0             	mov    %dx,%ax
     8e6:	66 c1 e0 02          	shl    $0x2,%ax
     8ea:	66 01 d0             	add    %dx,%ax
     8ed:	67 66 8d 14          	lea    (%si),%dx
     8f1:	85 00                	test   %eax,(%eax)
     8f3:	00 00                	add    %al,(%eax)
     8f5:	00 66 01             	add    %ah,0x1(%esi)
     8f8:	d0 66 29             	shlb   0x29(%esi)
     8fb:	c1 66 89 ca          	shll   $0xca,-0x77(%esi)
     8ff:	66 89 16             	mov    %dx,(%esi)
     902:	d0 1d 90 66 5d 66    	rcrb   0x665d6690
     908:	c3                   	ret    
     909:	90                   	nop
     90a:	66 55                	push   %bp
     90c:	66 89 e5             	mov    %sp,%bp
     90f:	90                   	nop
     910:	90                   	nop
     911:	66 5d                	pop    %bp
     913:	66 c3                	retw   
     915:	90                   	nop
     916:	66 55                	push   %bp
     918:	66 89 e5             	mov    %sp,%bp
     91b:	66 53                	push   %bx
     91d:	66 83 ec 10          	sub    $0x10,%sp
     921:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     928:	01 00                	add    %eax,(%eax)
     92a:	74 08                	je     0x934
     92c:	67 66 8b 45 08       	mov    0x8(%di),%ax
     931:	1e                   	push   %ds
     932:	8e d8                	mov    %eax,%ds
     934:	67 66 8b 55 0c       	mov    0xc(%di),%dx
     939:	67 66 8b 45 08       	mov    0x8(%di),%ax
     93e:	66 89 d3             	mov    %dx,%bx
     941:	67 66 8b 03          	mov    (%bp,%di),%ax
     945:	67 66 89 45 f8       	mov    %ax,-0x8(%di)
     94a:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     951:	01 00                	add    %eax,(%eax)
     953:	74 01                	je     0x956
     955:	1f                   	pop    %ds
     956:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
     95b:	66 83 c4 10          	add    $0x10,%sp
     95f:	66 5b                	pop    %bx
     961:	66 5d                	pop    %bp
     963:	66 c3                	retw   
     965:	90                   	nop
     966:	66 55                	push   %bp
     968:	66 89 e5             	mov    %sp,%bp
     96b:	66 53                	push   %bx
     96d:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     974:	01 00                	add    %eax,(%eax)
     976:	74 08                	je     0x980
     978:	67 66 8b 45 08       	mov    0x8(%di),%ax
     97d:	1e                   	push   %ds
     97e:	8e d8                	mov    %eax,%ds
     980:	67 66 8b 5d 0c       	mov    0xc(%di),%bx
     985:	67 8a 45 10          	mov    0x10(%di),%al
     989:	67 88 03             	mov    %al,(%bp,%di)
     98c:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     993:	01 00                	add    %eax,(%eax)
     995:	74 01                	je     0x998
     997:	1f                   	pop    %ds
     998:	90                   	nop
     999:	66 5b                	pop    %bx
     99b:	66 5d                	pop    %bp
     99d:	66 c3                	retw   
     99f:	90                   	nop
     9a0:	66 55                	push   %bp
     9a2:	66 89 e5             	mov    %sp,%bp
     9a5:	66 53                	push   %bx
     9a7:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     9ae:	01 00                	add    %eax,(%eax)
     9b0:	74 08                	je     0x9ba
     9b2:	67 66 8b 45 08       	mov    0x8(%di),%ax
     9b7:	1e                   	push   %ds
     9b8:	8e d8                	mov    %eax,%ds
     9ba:	67 66 8b 5d 0c       	mov    0xc(%di),%bx
     9bf:	67 8b 45 10          	mov    0x10(%di),%eax
     9c3:	67 89 03             	mov    %eax,(%bp,%di)
     9c6:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     9cd:	01 00                	add    %eax,(%eax)
     9cf:	74 01                	je     0x9d2
     9d1:	1f                   	pop    %ds
     9d2:	90                   	nop
     9d3:	66 5b                	pop    %bx
     9d5:	66 5d                	pop    %bp
     9d7:	66 c3                	retw   
     9d9:	90                   	nop
     9da:	66 55                	push   %bp
     9dc:	66 89 e5             	mov    %sp,%bp
     9df:	66 53                	push   %bx
     9e1:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     9e8:	01 00                	add    %eax,(%eax)
     9ea:	74 08                	je     0x9f4
     9ec:	67 66 8b 45 08       	mov    0x8(%di),%ax
     9f1:	1e                   	push   %ds
     9f2:	8e d8                	mov    %eax,%ds
     9f4:	67 66 8b 5d 0c       	mov    0xc(%di),%bx
     9f9:	67 66 8b 45 10       	mov    0x10(%di),%ax
     9fe:	67 66 89 03          	mov    %ax,(%bp,%di)
     a02:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     a09:	01 00                	add    %eax,(%eax)
     a0b:	74 01                	je     0xa0e
     a0d:	1f                   	pop    %ds
     a0e:	90                   	nop
     a0f:	66 5b                	pop    %bx
     a11:	66 5d                	pop    %bp
     a13:	66 c3                	retw   
     a15:	90                   	nop
     a16:	66 55                	push   %bp
     a18:	66 89 e5             	mov    %sp,%bp
     a1b:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     a22:	01 00                	add    %eax,(%eax)
     a24:	74 08                	je     0xa2e
     a26:	67 66 8b 45 08       	mov    0x8(%di),%ax
     a2b:	1e                   	push   %ds
     a2c:	8e d8                	mov    %eax,%ds
     a2e:	06                   	push   %es
     a2f:	67 66 81 7d 10 00 00 	cmpw   $0x0,0x10(%di)
     a36:	01 00                	add    %eax,(%eax)
     a38:	75 04                	jne    0xa3e
     a3a:	1e                   	push   %ds
     a3b:	07                   	pop    %es
     a3c:	eb 07                	jmp    0xa45
     a3e:	67 66 8b 45 10       	mov    0x10(%di),%ax
     a43:	8e c0                	mov    %eax,%es
     a45:	66 56                	push   %si
     a47:	66 57                	push   %di
     a49:	67 66 8b 75 0c       	mov    0xc(%di),%si
     a4e:	67 66 8b 7d 14       	mov    0x14(%di),%di
     a53:	67 66 8b 4d 18       	mov    0x18(%di),%cx
     a58:	fc                   	cld    
     a59:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
     a5b:	66 5f                	pop    %di
     a5d:	66 5e                	pop    %si
     a5f:	07                   	pop    %es
     a60:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     a67:	01 00                	add    %eax,(%eax)
     a69:	74 01                	je     0xa6c
     a6b:	1f                   	pop    %ds
     a6c:	90                   	nop
     a6d:	66 5d                	pop    %bp
     a6f:	66 c3                	retw   
     a71:	90                   	nop
     a72:	66 55                	push   %bp
     a74:	66 89 e5             	mov    %sp,%bp
     a77:	66 83 ec 28          	sub    $0x28,%sp
     a7b:	67 66 c7 44 24 04 00 	movw   $0x4,0x24(%si)
     a82:	00 00                	add    %al,(%eax)
     a84:	00 67 66             	add    %ah,0x66(%edi)
     a87:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     a8e:	66 e8 6a 00          	callw  0xafc
     a92:	00 00                	add    %al,(%eax)
     a94:	67 66 c7 45 f4 00 00 	movw   $0x0,-0xc(%di)
     a9b:	00 00                	add    %al,(%eax)
     a9d:	67 66 83 7d f4 19    	cmpw   $0x19,-0xc(%di)
     aa3:	74 3a                	je     0xadf
     aa5:	67 66 c7 45 f0 00 00 	movw   $0x0,-0x10(%di)
     aac:	00 00                	add    %al,(%eax)
     aae:	67 66 83 7d f0 50    	cmpw   $0x50,-0x10(%di)
     ab4:	74 21                	je     0xad7
     ab6:	67 66 c7 44 24 04 07 	movw   $0x704,0x24(%si)
     abd:	00 00                	add    %al,(%eax)
     abf:	00 67 66             	add    %ah,0x66(%edi)
     ac2:	c7 04 24 20 00 00 00 	movl   $0x20,(%esp)
     ac9:	66 e8 43 fd          	callw  0x810
     acd:	ff                   	(bad)  
     ace:	ff 67 66             	jmp    *0x66(%edi)
     ad1:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
     ad5:	eb d7                	jmp    0xaae
     ad7:	67 66 83 45 f4 01    	addw   $0x1,-0xc(%di)
     add:	eb be                	jmp    0xa9d
     adf:	67 66 c7 44 24 04 00 	movw   $0x4,0x24(%si)
     ae6:	00 00                	add    %al,(%eax)
     ae8:	00 67 66             	add    %ah,0x66(%edi)
     aeb:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     af2:	66 e8 06 00          	callw  0xafc
     af6:	00 00                	add    %al,(%eax)
     af8:	90                   	nop
     af9:	66 c9                	leavew 
     afb:	66 c3                	retw   
     afd:	90                   	nop
     afe:	66 55                	push   %bp
     b00:	66 89 e5             	mov    %sp,%bp
     b03:	67 66 8b 4d 08       	mov    0x8(%di),%cx
     b08:	66 ba 1f 85          	mov    $0x851f,%dx
     b0c:	eb 51                	jmp    0xb5f
     b0e:	66 89 c8             	mov    %cx,%ax
     b11:	66 f7 ea             	imul   %dx
     b14:	66 c1 fa 03          	sar    $0x3,%dx
     b18:	66 89 c8             	mov    %cx,%ax
     b1b:	66 c1 f8 1f          	sar    $0x1f,%ax
     b1f:	66 29 c2             	sub    %ax,%dx
     b22:	66 89 d0             	mov    %dx,%ax
     b25:	66 c1 e0 02          	shl    $0x2,%ax
     b29:	66 01 d0             	add    %dx,%ax
     b2c:	67 66 8d 14          	lea    (%si),%dx
     b30:	85 00                	test   %eax,(%eax)
     b32:	00 00                	add    %al,(%eax)
     b34:	00 66 01             	add    %ah,0x1(%esi)
     b37:	d0 66 29             	shlb   0x29(%esi)
     b3a:	c1 66 89 ca          	shll   $0xca,-0x77(%esi)
     b3e:	66 89 16             	mov    %dx,(%esi)
     b41:	d0 1d 67 66 8b 4d    	rcrb   0x4d8b6667
     b47:	0c 66                	or     $0x66,%al
     b49:	ba 67 66 66 66       	mov    $0x66666667,%edx
     b4e:	66 89 c8             	mov    %cx,%ax
     b51:	66 f7 ea             	imul   %dx
     b54:	66 c1 fa 05          	sar    $0x5,%dx
     b58:	66 89 c8             	mov    %cx,%ax
     b5b:	66 c1 f8 1f          	sar    $0x1f,%ax
     b5f:	66 29 c2             	sub    %ax,%dx
     b62:	66 89 d0             	mov    %dx,%ax
     b65:	66 c1 e0 02          	shl    $0x2,%ax
     b69:	66 01 d0             	add    %dx,%ax
     b6c:	66 c1 e0 04          	shl    $0x4,%ax
     b70:	66 29 c1             	sub    %ax,%cx
     b73:	66 89 ca             	mov    %cx,%dx
     b76:	66 89 16             	mov    %dx,(%esi)
     b79:	d4 1d                	aam    $0x1d
     b7b:	90                   	nop
     b7c:	66 5d                	pop    %bp
     b7e:	66 c3                	retw   
     b80:	66 55                	push   %bp
     b82:	66 89 e5             	mov    %sp,%bp
     b85:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     b8c:	01 00                	add    %eax,(%eax)
     b8e:	74 08                	je     0xb98
     b90:	67 66 8b 45 08       	mov    0x8(%di),%ax
     b95:	1e                   	push   %ds
     b96:	8e d8                	mov    %eax,%ds
     b98:	90                   	nop
     b99:	66 5d                	pop    %bp
     b9b:	66 c3                	retw   
     b9d:	90                   	nop
     b9e:	66 55                	push   %bp
     ba0:	66 89 e5             	mov    %sp,%bp
     ba3:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     baa:	01 00                	add    %eax,(%eax)
     bac:	74 01                	je     0xbaf
     bae:	1f                   	pop    %ds
     baf:	90                   	nop
     bb0:	66 5d                	pop    %bp
     bb2:	66 c3                	retw   
     bb4:	66 55                	push   %bp
     bb6:	66 89 e5             	mov    %sp,%bp
     bb9:	06                   	push   %es
     bba:	67 66 81 7d 08 00 00 	cmpw   $0x0,0x8(%di)
     bc1:	01 00                	add    %eax,(%eax)
     bc3:	75 04                	jne    0xbc9
     bc5:	1e                   	push   %ds
     bc6:	07                   	pop    %es
     bc7:	eb 07                	jmp    0xbd0
     bc9:	67 66 8b 45 08       	mov    0x8(%di),%ax
     bce:	8e c0                	mov    %eax,%es
     bd0:	90                   	nop
     bd1:	66 5d                	pop    %bp
     bd3:	66 c3                	retw   
     bd5:	90                   	nop
     bd6:	66 55                	push   %bp
     bd8:	66 89 e5             	mov    %sp,%bp
     bdb:	07                   	pop    %es
     bdc:	90                   	nop
     bdd:	66 5d                	pop    %bp
     bdf:	66 c3                	retw   
     be1:	90                   	nop
     be2:	66 55                	push   %bp
     be4:	66 89 e5             	mov    %sp,%bp
     be7:	66 83 ec 10          	sub    $0x10,%sp
     beb:	06                   	push   %es
     bec:	67 66 8b 45 08       	mov    0x8(%di),%ax
     bf1:	8e c0                	mov    %eax,%es
     bf3:	67 8b 5d 0c          	mov    0xc(%di),%ebx
     bf7:	67 8a 55 10          	mov    0x10(%di),%dl
     bfb:	67 8a 75 18          	mov    0x18(%di),%dh
     bff:	67 8b 4d 14          	mov    0x14(%di),%ecx
     c03:	c1 e1 06             	shl    $0x6,%ecx
     c06:	67 02 4d 1c          	add    0x1c(%di),%cl
     c0a:	b4 02                	mov    $0x2,%ah
     c0c:	67 8a 45 20          	mov    0x20(%di),%al
     c10:	cd 13                	int    $0x13
     c12:	07                   	pop    %es
     c13:	66 31 c0             	xor    %ax,%ax
     c16:	72 06                	jb     0xc1e
     c18:	66 b8 01 00          	mov    $0x1,%ax
     c1c:	00 00                	add    %al,(%eax)
     c1e:	67 66 89 45 fc       	mov    %ax,-0x4(%di)
     c23:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
     c28:	66 c9                	leavew 
     c2a:	66 c3                	retw   
     c2c:	66 55                	push   %bp
     c2e:	66 89 e5             	mov    %sp,%bp
     c31:	66 56                	push   %si
     c33:	66 53                	push   %bx
     c35:	66 83 ec 1c          	sub    $0x1c,%sp
     c39:	67 66 8b 4d 14       	mov    0x14(%di),%cx
     c3e:	66 ba 39 8e          	mov    $0x8e39,%dx
     c42:	e3 38                	jecxz  0xc7c
     c44:	66 89 c8             	mov    %cx,%ax
     c47:	66 f7 ea             	imul   %dx
     c4a:	66 c1 fa 02          	sar    $0x2,%dx
     c4e:	66 89 c8             	mov    %cx,%ax
     c51:	66 c1 f8 1f          	sar    $0x1f,%ax
     c55:	66 29 c2             	sub    %ax,%dx
     c58:	66 89 d0             	mov    %dx,%ax
     c5b:	66 c1 e0 03          	shl    $0x3,%ax
     c5f:	66 01 d0             	add    %dx,%ax
     c62:	66 01 c0             	add    %ax,%ax
     c65:	66 29 c1             	sub    %ax,%cx
     c68:	66 89 ca             	mov    %cx,%dx
     c6b:	67 66 8d 72 01       	lea    0x1(%bp,%si),%si
     c70:	67 66 8b 5d 14       	mov    0x14(%di),%bx
     c75:	66 ba 39 8e          	mov    $0x8e39,%dx
     c79:	e3 38                	jecxz  0xcb3
     c7b:	66 89 d8             	mov    %bx,%ax
     c7e:	66 f7 ea             	imul   %dx
     c81:	66 c1 fa 03          	sar    $0x3,%dx
     c85:	66 89 d8             	mov    %bx,%ax
     c88:	66 c1 f8 1f          	sar    $0x1f,%ax
     c8c:	66 89 d1             	mov    %dx,%cx
     c8f:	66 29 c1             	sub    %ax,%cx
     c92:	66 89 c8             	mov    %cx,%ax
     c95:	66 c1 e0 03          	shl    $0x3,%ax
     c99:	66 01 c8             	add    %cx,%ax
     c9c:	66 c1 e0 02          	shl    $0x2,%ax
     ca0:	66 29 c3             	sub    %ax,%bx
     ca3:	66 89 d9             	mov    %bx,%cx
     ca6:	66 ba 39 8e          	mov    $0x8e39,%dx
     caa:	e3 38                	jecxz  0xce4
     cac:	66 89 c8             	mov    %cx,%ax
     caf:	66 f7 ea             	imul   %dx
     cb2:	66 c1 fa 02          	sar    $0x2,%dx
     cb6:	66 89 c8             	mov    %cx,%ax
     cb9:	66 c1 f8 1f          	sar    $0x1f,%ax
     cbd:	66 89 d3             	mov    %dx,%bx
     cc0:	66 29 c3             	sub    %ax,%bx
     cc3:	67 66 8b 4d 14       	mov    0x14(%di),%cx
     cc8:	66 ba 39 8e          	mov    $0x8e39,%dx
     ccc:	e3 38                	jecxz  0xd06
     cce:	66 89 c8             	mov    %cx,%ax
     cd1:	66 f7 ea             	imul   %dx
     cd4:	66 c1 fa 03          	sar    $0x3,%dx
     cd8:	66 89 c8             	mov    %cx,%ax
     cdb:	66 c1 f8 1f          	sar    $0x1f,%ax
     cdf:	66 29 c2             	sub    %ax,%dx
     ce2:	67 66 8b 45 18       	mov    0x18(%di),%ax
     ce7:	67 66 89 44 24       	mov    %ax,0x24(%si)
     cec:	18 67 66             	sbb    %ah,0x66(%edi)
     cef:	89 74 24 14          	mov    %esi,0x14(%esp)
     cf3:	67 66 89 5c 24       	mov    %bx,0x24(%si)
     cf8:	10 67 66             	adc    %ah,0x66(%edi)
     cfb:	89 54 24 0c          	mov    %edx,0xc(%esp)
     cff:	67 66 8b 45 10       	mov    0x10(%di),%ax
     d04:	67 66 89 44 24       	mov    %ax,0x24(%si)
     d09:	08 67 66             	or     %ah,0x66(%edi)
     d0c:	8b 45 0c             	mov    0xc(%ebp),%eax
     d0f:	67 66 89 44 24       	mov    %ax,0x24(%si)
     d14:	04 67                	add    $0x67,%al
     d16:	66 8b 45 08          	mov    0x8(%ebp),%ax
     d1a:	67 66 89 04          	mov    %ax,(%si)
     d1e:	24 66                	and    $0x66,%al
     d20:	e8 bd fe ff ff       	call   0xbe2
     d25:	66 83 c4 1c          	add    $0x1c,%sp
     d29:	66 5b                	pop    %bx
     d2b:	66 5e                	pop    %si
     d2d:	66 5d                	pop    %bp
     d2f:	66 c3                	retw   
     d31:	90                   	nop
     d32:	90                   	nop
     d33:	90                   	nop
     d34:	66 55                	push   %bp
     d36:	66 89 e5             	mov    %sp,%bp
     d39:	66 83 ec 04          	sub    $0x4,%sp
     d3d:	67 66 89 4d fc       	mov    %cx,-0x4(%di)
     d42:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
     d47:	67 66 8b 55 08       	mov    0x8(%di),%dx
     d4c:	67 66 89 10          	mov    %dx,(%bx,%si)
     d50:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
     d55:	67 66 8b 55 0c       	mov    0xc(%di),%dx
     d5a:	67 66 89 50 04       	mov    %dx,0x4(%bx,%si)
     d5f:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
     d64:	67 66 8b 55 10       	mov    0x10(%di),%dx
     d69:	67 66 89 50 08       	mov    %dx,0x8(%bx,%si)
     d6e:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
     d73:	67 66 8b 55 14       	mov    0x14(%di),%dx
     d78:	67 66 89 50 0c       	mov    %dx,0xc(%bx,%si)
     d7d:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
     d82:	67 66 8b 55 18       	mov    0x18(%di),%dx
     d87:	67 66 89 50 10       	mov    %dx,0x10(%bx,%si)
     d8c:	90                   	nop
     d8d:	66 c9                	leavew 
     d8f:	66 c2 14 00          	retw   $0x14
     d93:	90                   	nop
     d94:	66 55                	push   %bp
     d96:	66 89 e5             	mov    %sp,%bp
     d99:	66 83 ec 04          	sub    $0x4,%sp
     d9d:	67 66 89 4d fc       	mov    %cx,-0x4(%di)
     da2:	90                   	nop
     da3:	66 c9                	leavew 
     da5:	66 c3                	retw   
     da7:	90                   	nop
     da8:	66 55                	push   %bp
     daa:	66 89 e5             	mov    %sp,%bp
     dad:	66 83 ec 04          	sub    $0x4,%sp
     db1:	67 66 89 4d fc       	mov    %cx,-0x4(%di)
     db6:	e4 92                	in     $0x92,%al
     db8:	0c 02                	or     $0x2,%al
     dba:	e6 92                	out    %al,$0x92
     dbc:	90                   	nop
     dbd:	66 c9                	leavew 
     dbf:	66 c3                	retw   
     dc1:	90                   	nop
     dc2:	66 55                	push   %bp
     dc4:	66 89 e5             	mov    %sp,%bp
     dc7:	66 83 ec 08          	sub    $0x8,%sp
     dcb:	67 66 89 4d fc       	mov    %cx,-0x4(%di)
     dd0:	67 66 8b 45 08       	mov    0x8(%di),%ax
     dd5:	67 89 45 f8          	mov    %eax,-0x8(%di)
     dd9:	67 8b 45 08          	mov    0x8(%di),%eax
     ddd:	67 89 45 0a          	mov    %eax,0xa(%di)
     de1:	67 0f 01 5d 0a       	lidtl  0xa(%di)
     de6:	90                   	nop
     de7:	66 c9                	leavew 
     de9:	66 c2 08 00          	retw   $0x8
     ded:	90                   	nop
     dee:	66 55                	push   %bp
     df0:	66 89 e5             	mov    %sp,%bp
     df3:	66 83 ec 08          	sub    $0x8,%sp
     df7:	67 66 89 4d fc       	mov    %cx,-0x4(%di)
     dfc:	67 66 8b 45 08       	mov    0x8(%di),%ax
     e01:	67 89 45 f8          	mov    %eax,-0x8(%di)
     e05:	67 8b 45 08          	mov    0x8(%di),%eax
     e09:	67 89 45 0a          	mov    %eax,0xa(%di)
     e0d:	67 0f 01 55 0a       	lgdtl  0xa(%di)
     e12:	90                   	nop
     e13:	66 c9                	leavew 
     e15:	66 c2 08 00          	retw   $0x8
     e19:	90                   	nop
     e1a:	66 55                	push   %bp
     e1c:	66 89 e5             	mov    %sp,%bp
     e1f:	66 83 ec 04          	sub    $0x4,%sp
     e23:	67 66 89 4d fc       	mov    %cx,-0x4(%di)
     e28:	0f 20 c0             	mov    %cr0,%eax
     e2b:	66 83 c8 01          	or     $0x1,%ax
     e2f:	0f 22 c0             	mov    %eax,%cr0
     e32:	ea 00 08 10 00 90 66 	ljmp   $0x6690,$0x100800
     e39:	c9                   	leave  
     e3a:	66 c3                	retw   
     e3c:	66 55                	push   %bp
     e3e:	66 89 e5             	mov    %sp,%bp
     e41:	66 56                	push   %si
     e43:	66 53                	push   %bx
     e45:	66 83 ec 30          	sub    $0x30,%sp
     e49:	67 66 89 4d f4       	mov    %cx,-0xc(%di)
     e4e:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
     e53:	67 66 8b 40 0c       	mov    0xc(%bx,%si),%ax
     e58:	66 3d 0a 0a          	cmp    $0xa0a,%ax
     e5c:	00 00                	add    %al,(%eax)
     e5e:	0f 8f 9a 00 67 66    	jg     0x66670efe
     e64:	8b 45 f4             	mov    -0xc(%ebp),%eax
     e67:	67 66 8b 48 08       	mov    0x8(%bx,%si),%cx
     e6c:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
     e71:	67 66 8b 50 04       	mov    0x4(%bx,%si),%dx
     e76:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
     e7b:	67 66 8b 00          	mov    (%bx,%si),%ax
     e7f:	67 66 89 4c 24       	mov    %cx,0x24(%si)
     e84:	10 67 66             	adc    %ah,0x66(%edi)
     e87:	89 54 24 0c          	mov    %edx,0xc(%esp)
     e8b:	67 66 89 44 24       	mov    %ax,0x24(%si)
     e90:	08 67 66             	or     %ah,0x66(%edi)
     e93:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
     e9a:	00 
     e9b:	67 66 c7 04 24 0b    	movw   $0xb24,(%si)
     ea1:	0a 00                	or     (%eax),%al
     ea3:	00 66 e8             	add    %ah,-0x18(%esi)
     ea6:	82                   	(bad)  
     ea7:	fd                   	std    
     ea8:	ff                   	(bad)  
     ea9:	ff 67 66             	jmp    *0x66(%edi)
     eac:	8b 45 f4             	mov    -0xc(%ebp),%eax
     eaf:	67 66 8b 40 08       	mov    0x8(%bx,%si),%ax
     eb4:	66 c1 e0 09          	shl    $0x9,%ax
     eb8:	66 89 c1             	mov    %ax,%cx
     ebb:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
     ec0:	67 66 8b 50 10       	mov    0x10(%bx,%si),%dx
     ec5:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
     eca:	67 66 8b 40 0c       	mov    0xc(%bx,%si),%ax
     ecf:	67 66 89 4c 24       	mov    %cx,0x24(%si)
     ed4:	10 67 66             	adc    %ah,0x66(%edi)
     ed7:	89 54 24 0c          	mov    %edx,0xc(%esp)
     edb:	67 66 89 44 24       	mov    %ax,0x24(%si)
     ee0:	08 67 66             	or     %ah,0x66(%edi)
     ee3:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
     eea:	00 
     eeb:	67 66 c7 04 24 0b    	movw   $0xb24,(%si)
     ef1:	0a 00                	or     (%eax),%al
     ef3:	00 66 e8             	add    %ah,-0x18(%esi)
     ef6:	1c fb                	sbb    $0xfb,%al
     ef8:	ff                   	(bad)  
     ef9:	ff                   	(bad)  
     efa:	eb 54                	jmp    0xf50
     efc:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
     f01:	67 66 8b 70 08       	mov    0x8(%bx,%si),%si
     f06:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
     f0b:	67 66 8b 58 04       	mov    0x4(%bx,%si),%bx
     f10:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
     f15:	67 66 8b 08          	mov    (%bx,%si),%cx
     f19:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
     f1e:	67 66 8b 50 10       	mov    0x10(%bx,%si),%dx
     f23:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
     f28:	67 66 8b 40 0c       	mov    0xc(%bx,%si),%ax
     f2d:	67 66 89 74 24       	mov    %si,0x24(%si)
     f32:	10 67 66             	adc    %ah,0x66(%edi)
     f35:	89 5c 24 0c          	mov    %ebx,0xc(%esp)
     f39:	67 66 89 4c 24       	mov    %cx,0x24(%si)
     f3e:	08 67 66             	or     %ah,0x66(%edi)
     f41:	89 54 24 04          	mov    %edx,0x4(%esp)
     f45:	67 66 89 04          	mov    %ax,(%si)
     f49:	24 66                	and    $0x66,%al
     f4b:	e8 dc fc ff ff       	call   0xc2c
     f50:	90                   	nop
     f51:	66 83 c4 30          	add    $0x30,%sp
     f55:	66 5b                	pop    %bx
     f57:	66 5e                	pop    %si
     f59:	66 5d                	pop    %bp
     f5b:	66 c3                	retw   
     f5d:	90                   	nop
     f5e:	66 55                	push   %bp
     f60:	66 89 e5             	mov    %sp,%bp
     f63:	66 81 ec 98 00       	sub    $0x98,%sp
     f68:	00 00                	add    %al,(%eax)
     f6a:	67 66 89 4d 94       	mov    %cx,-0x6c(%di)
     f6f:	67 66 8b 55 0c       	mov    0xc(%di),%dx
     f74:	67 66 8b 45 14       	mov    0x14(%di),%ax
     f79:	67 89 55 90          	mov    %edx,-0x70(%di)
     f7d:	67 89 45 8c          	mov    %eax,-0x74(%di)
     f81:	67 66 8b 45 94       	mov    -0x6c(%di),%ax
     f86:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
     f8b:	66 a1 c0 1d 66 0f    	mov    0xf661dc0,%ax
     f91:	be c8 66 a1 78       	mov    $0x78a166c8,%esi
     f96:	1d 66 0f be d0       	sbb    $0xd0be0f66,%eax
     f9b:	67 66 8d 45 d6       	lea    -0x2a(%di),%ax
     fa0:	67 66 c7 44 24 18 01 	movw   $0x118,0x24(%si)
     fa7:	00 00                	add    %al,(%eax)
     fa9:	00 67 66             	add    %ah,0x66(%edi)
     fac:	c7 44 24 14 01 00 00 	movl   $0x1,0x14(%esp)
     fb3:	00 
     fb4:	67 66 c7 44 24 10 01 	movw   $0x110,0x24(%si)
     fbb:	00 00                	add    %al,(%eax)
     fbd:	00 67 66             	add    %ah,0x66(%edi)
     fc0:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
     fc4:	67 66 89 54 24       	mov    %dx,0x24(%si)
     fc9:	08 67 66             	or     %ah,0x66(%edi)
     fcc:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
     fd3:	00 
     fd4:	67 66 c7 04 24 00    	movw   $0x24,(%si)
     fda:	00 00                	add    %al,(%eax)
     fdc:	00 66 89             	add    %ah,-0x77(%esi)
     fdf:	c1 66 e8 00          	shll   $0x0,-0x18(%esi)
     fe3:	04 00                	add    $0x0,%al
     fe5:	00 66 83             	add    %ah,-0x7d(%esi)
     fe8:	ec                   	in     (%dx),%al
     fe9:	1c 66                	sbb    $0x66,%al
     feb:	a1 7c 1d 66 0f       	mov    0xf661d7c,%eax
     ff0:	be d0 67 66 8d       	mov    $0x8d6667d0,%esi
     ff5:	45                   	inc    %ebp
     ff6:	c7                   	(bad)  
     ff7:	67 66 c7 44 24 18 01 	movw   $0x118,0x24(%si)
     ffe:	00 00                	add    %al,(%eax)
    1000:	00 67 66             	add    %ah,0x66(%edi)
    1003:	c7 44 24 14 01 00 00 	movl   $0x1,0x14(%esp)
    100a:	00 
    100b:	67 66 c7 44 24 10 01 	movw   $0x110,0x24(%si)
    1012:	00 00                	add    %al,(%eax)
    1014:	00 67 66             	add    %ah,0x66(%edi)
    1017:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
    101e:	00 
    101f:	67 66 89 54 24       	mov    %dx,0x24(%si)
    1024:	08 67 66             	or     %ah,0x66(%edi)
    1027:	8b 55 1c             	mov    0x1c(%ebp),%edx
    102a:	67 66 89 54 24       	mov    %dx,0x24(%si)
    102f:	04 67                	add    $0x67,%al
    1031:	66 c7 04 24 00 00    	movw   $0x0,(%esp)
    1037:	00 00                	add    %al,(%eax)
    1039:	66 89 c1             	mov    %ax,%cx
    103c:	66 e8 a4 03          	callw  0x13e4
    1040:	00 00                	add    %al,(%eax)
    1042:	66 83 ec 1c          	sub    $0x1c,%sp
    1046:	66 a1 78 1d 66 0f    	mov    0xf661d78,%ax
    104c:	be d0 67 66 8d       	mov    $0x8d6667d0,%esi
    1051:	45                   	inc    %ebp
    1052:	b8 67 66 c7 44       	mov    $0x44c76667,%eax
    1057:	24 18                	and    $0x18,%al
    1059:	01 00                	add    %eax,(%eax)
    105b:	00 00                	add    %al,(%eax)
    105d:	67 66 c7 44 24 14 01 	movw   $0x114,0x24(%si)
    1064:	00 00                	add    %al,(%eax)
    1066:	00 67 66             	add    %ah,0x66(%edi)
    1069:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
    1070:	00 
    1071:	67 66 c7 44 24 0c 00 	movw   $0xc,0x24(%si)
    1078:	00 00                	add    %al,(%eax)
    107a:	00 67 66             	add    %ah,0x66(%edi)
    107d:	89 54 24 08          	mov    %edx,0x8(%esp)
    1081:	67 66 8b 55 1c       	mov    0x1c(%di),%dx
    1086:	67 66 89 54 24       	mov    %dx,0x24(%si)
    108b:	04 67                	add    $0x67,%al
    108d:	66 c7 04 24 00 00    	movw   $0x0,(%esp)
    1093:	00 00                	add    %al,(%eax)
    1095:	66 89 c1             	mov    %ax,%cx
    1098:	66 e8 48 03          	callw  0x13e4
    109c:	00 00                	add    %al,(%eax)
    109e:	66 83 ec 1c          	sub    $0x1c,%sp
    10a2:	66 a1 70 1d 66 0f    	mov    0xf661d70,%ax
    10a8:	be d0 67 66 8d       	mov    $0x8d6667d0,%esi
    10ad:	45                   	inc    %ebp
    10ae:	a9 67 66 c7 44       	test   $0x44c76667,%eax
    10b3:	24 18                	and    $0x18,%al
    10b5:	01 00                	add    %eax,(%eax)
    10b7:	00 00                	add    %al,(%eax)
    10b9:	67 66 c7 44 24 14 01 	movw   $0x114,0x24(%si)
    10c0:	00 00                	add    %al,(%eax)
    10c2:	00 67 66             	add    %ah,0x66(%edi)
    10c5:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
    10cc:	00 
    10cd:	67 66 c7 44 24 0c 00 	movw   $0xc,0x24(%si)
    10d4:	00 00                	add    %al,(%eax)
    10d6:	00 67 66             	add    %ah,0x66(%edi)
    10d9:	89 54 24 08          	mov    %edx,0x8(%esp)
    10dd:	67 66 8b 55 20       	mov    0x20(%di),%dx
    10e2:	67 66 89 54 24       	mov    %dx,0x24(%si)
    10e7:	04 67                	add    $0x67,%al
    10e9:	66 c7 04 24 00 00    	movw   $0x0,(%esp)
    10ef:	00 00                	add    %al,(%eax)
    10f1:	66 89 c1             	mov    %ax,%cx
    10f4:	66 e8 ec 02          	callw  0x13e4
    10f8:	00 00                	add    %al,(%eax)
    10fa:	66 83 ec 1c          	sub    $0x1c,%sp
    10fe:	66 a1 78 1d 66 0f    	mov    0xf661d78,%ax
    1104:	be d0 67 66 8d       	mov    $0x8d6667d0,%esi
    1109:	45                   	inc    %ebp
    110a:	9a 67 66 c7 44 24 18 	lcall  $0x1824,$0x44c76667
    1111:	01 00                	add    %eax,(%eax)
    1113:	00 00                	add    %al,(%eax)
    1115:	67 66 c7 44 24 14 01 	movw   $0x114,0x24(%si)
    111c:	00 00                	add    %al,(%eax)
    111e:	00 67 66             	add    %ah,0x66(%edi)
    1121:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
    1128:	00 
    1129:	67 66 c7 44 24 0c 00 	movw   $0xc,0x24(%si)
    1130:	00 00                	add    %al,(%eax)
    1132:	00 67 66             	add    %ah,0x66(%edi)
    1135:	89 54 24 08          	mov    %edx,0x8(%esp)
    1139:	67 66 c7 44 24 04 a0 	movw   $0xa004,0x24(%si)
    1140:	0f 00 00             	sldt   (%eax)
    1143:	67 66 c7 04 24 00    	movw   $0x24,(%si)
    1149:	80 0b 00             	orb    $0x0,(%ebx)
    114c:	66 89 c1             	mov    %ax,%cx
    114f:	66 e8 91 02          	callw  0x13e4
    1153:	00 00                	add    %al,(%eax)
    1155:	66 83 ec 1c          	sub    $0x1c,%sp
    1159:	66 a1 78 1d 66 0f    	mov    0xf661d78,%ax
    115f:	be d0 66 a1 c0       	mov    $0xc0a166d0,%esi
    1164:	1d 66 0f be c8       	sbb    $0xc8be0f66,%eax
    1169:	67 66 8d 45 e5       	lea    -0x1b(%di),%ax
    116e:	67 66 c7 44 24 18 01 	movw   $0x118,0x24(%si)
    1175:	00 00                	add    %al,(%eax)
    1177:	00 67 66             	add    %ah,0x66(%edi)
    117a:	c7 44 24 14 01 00 00 	movl   $0x1,0x14(%esp)
    1181:	00 
    1182:	67 66 c7 44 24 10 01 	movw   $0x110,0x24(%si)
    1189:	00 00                	add    %al,(%eax)
    118b:	00 67 66             	add    %ah,0x66(%edi)
    118e:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
    1192:	67 66 89 54 24       	mov    %dx,0x24(%si)
    1197:	08 67 66             	or     %ah,0x66(%edi)
    119a:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
    11a1:	00 
    11a2:	67 66 c7 04 24 00    	movw   $0x24,(%si)
    11a8:	00 00                	add    %al,(%eax)
    11aa:	00 66 89             	add    %ah,-0x77(%esi)
    11ad:	c1 66 e8 32          	shll   $0x32,-0x18(%esi)
    11b1:	02 00                	add    (%eax),%al
    11b3:	00 66 83             	add    %ah,-0x7d(%esi)
    11b6:	ec                   	in     (%dx),%al
    11b7:	1c 67                	sbb    $0x67,%al
    11b9:	66 8b 45 e5          	mov    -0x1b(%ebp),%ax
    11bd:	67 66 89 45 d6       	mov    %ax,-0x2a(%di)
    11c2:	67 66 8b 45 e9       	mov    -0x17(%di),%ax
    11c7:	67 66 89 45 da       	mov    %ax,-0x26(%di)
    11cc:	67 66 8b 45 ed       	mov    -0x13(%di),%ax
    11d1:	67 66 89 45 de       	mov    %ax,-0x22(%di)
    11d6:	67 66 0f b7 45 f1    	movzww -0xf(%di),%ax
    11dc:	67 89 45 e2          	mov    %eax,-0x1e(%di)
    11e0:	67 66 0f b6 45 f3    	movzbw -0xd(%di),%ax
    11e6:	67 88 45 e4          	mov    %al,-0x1c(%di)
    11ea:	67 66 8d 45 e5       	lea    -0x1b(%di),%ax
    11ef:	66 89 c1             	mov    %ax,%cx
    11f2:	66 e8 cc 01          	callw  0x13c2
    11f6:	00 00                	add    %al,(%eax)
    11f8:	67 66 8b 55 10       	mov    0x10(%di),%dx
    11fd:	67 66 8d 45 d6       	lea    -0x2a(%di),%ax
    1202:	67 66 89 54 24       	mov    %dx,0x24(%si)
    1207:	04 67                	add    $0x67,%al
    1209:	66 c7 04 24 00 00    	movw   $0x0,(%esp)
    120f:	00 00                	add    %al,(%eax)
    1211:	66 89 c1             	mov    %ax,%cx
    1214:	66 e8 14 04          	callw  0x162c
    1218:	00 00                	add    %al,(%eax)
    121a:	66 83 ec 08          	sub    $0x8,%sp
    121e:	67 66 8b 45 10       	mov    0x10(%di),%ax
    1223:	66 83 c0 08          	add    $0x8,%ax
    1227:	66 89 c2             	mov    %ax,%dx
    122a:	67 66 8d 45 9a       	lea    -0x66(%di),%ax
    122f:	67 66 89 54 24       	mov    %dx,0x24(%si)
    1234:	04 67                	add    $0x67,%al
    1236:	66 c7 04 24 00 00    	movw   $0x0,(%esp)
    123c:	00 00                	add    %al,(%eax)
    123e:	66 89 c1             	mov    %ax,%cx
    1241:	66 e8 e7 03          	callw  0x162c
    1245:	00 00                	add    %al,(%eax)
    1247:	66 83 ec 08          	sub    $0x8,%sp
    124b:	67 66 8b 45 10       	mov    0x10(%di),%ax
    1250:	66 83 c0 10          	add    $0x10,%ax
    1254:	66 89 c2             	mov    %ax,%dx
    1257:	67 66 8d 45 c7       	lea    -0x39(%di),%ax
    125c:	67 66 89 54 24       	mov    %dx,0x24(%si)
    1261:	04 67                	add    $0x67,%al
    1263:	66 c7 04 24 00 00    	movw   $0x0,(%esp)
    1269:	00 00                	add    %al,(%eax)
    126b:	66 89 c1             	mov    %ax,%cx
    126e:	66 e8 ba 03          	callw  0x162c
    1272:	00 00                	add    %al,(%eax)
    1274:	66 83 ec 08          	sub    $0x8,%sp
    1278:	67 66 8b 45 10       	mov    0x10(%di),%ax
    127d:	66 83 c0 18          	add    $0x18,%ax
    1281:	66 89 c2             	mov    %ax,%dx
    1284:	67 66 8d 45 b8       	lea    -0x48(%di),%ax
    1289:	67 66 89 54 24       	mov    %dx,0x24(%si)
    128e:	04 67                	add    $0x67,%al
    1290:	66 c7 04 24 00 00    	movw   $0x0,(%esp)
    1296:	00 00                	add    %al,(%eax)
    1298:	66 89 c1             	mov    %ax,%cx
    129b:	66 e8 8d 03          	callw  0x162c
    129f:	00 00                	add    %al,(%eax)
    12a1:	66 83 ec 08          	sub    $0x8,%sp
    12a5:	67 66 8b 45 10       	mov    0x10(%di),%ax
    12aa:	66 83 c0 20          	add    $0x20,%ax
    12ae:	66 89 c2             	mov    %ax,%dx
    12b1:	67 66 8d 45 a9       	lea    -0x57(%di),%ax
    12b6:	67 66 89 54 24       	mov    %dx,0x24(%si)
    12bb:	04 67                	add    $0x67,%al
    12bd:	66 c7 04 24 00 00    	movw   $0x0,(%esp)
    12c3:	00 00                	add    %al,(%eax)
    12c5:	66 89 c1             	mov    %ax,%cx
    12c8:	66 e8 60 03          	callw  0x162c
    12cc:	00 00                	add    %al,(%eax)
    12ce:	66 83 ec 08          	sub    $0x8,%sp
    12d2:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    12d7:	66 89 c1             	mov    %ax,%cx
    12da:	66 e8 5c fb          	callw  0xe3a
    12de:	ff                   	(bad)  
    12df:	ff 67 66             	jmp    *0x66(%edi)
    12e2:	8b 45 f4             	mov    -0xc(%ebp),%eax
    12e5:	66 89 c1             	mov    %ax,%cx
    12e8:	66 e8 ba fa          	callw  0xda6
    12ec:	ff                   	(bad)  
    12ed:	ff 67 66             	jmp    *0x66(%edi)
    12f0:	0f bf 55 90          	movswl -0x70(%ebp),%edx
    12f4:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    12f9:	67 66 8b 4d 08       	mov    0x8(%di),%cx
    12fe:	67 66 89 4c 24       	mov    %cx,0x24(%si)
    1303:	04 67                	add    $0x67,%al
    1305:	66 89 14 24          	mov    %dx,(%esp)
    1309:	66 89 c1             	mov    %ax,%cx
    130c:	66 e8 b0 fa          	callw  0xdc0
    1310:	ff                   	(bad)  
    1311:	ff 66 83             	jmp    *-0x7d(%esi)
    1314:	ec                   	in     (%dx),%al
    1315:	08 67 66             	or     %ah,0x66(%edi)
    1318:	0f bf 55 8c          	movswl -0x74(%ebp),%edx
    131c:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1321:	67 66 8b 4d 10       	mov    0x10(%di),%cx
    1326:	67 66 89 4c 24       	mov    %cx,0x24(%si)
    132b:	04 67                	add    $0x67,%al
    132d:	66 89 14 24          	mov    %dx,(%esp)
    1331:	66 89 c1             	mov    %ax,%cx
    1334:	66 e8 b4 fa          	callw  0xdec
    1338:	ff                   	(bad)  
    1339:	ff 66 83             	jmp    *-0x7d(%esi)
    133c:	ec                   	in     (%dx),%al
    133d:	08 67 66             	or     %ah,0x66(%edi)
    1340:	8b 45 f4             	mov    -0xc(%ebp),%eax
    1343:	66 89 c1             	mov    %ax,%cx
    1346:	66 e8 ce fa          	callw  0xe18
    134a:	ff                   	(bad)  
    134b:	ff 67 66             	jmp    *0x66(%edi)
    134e:	8d 45 9a             	lea    -0x66(%ebp),%eax
    1351:	66 89 c1             	mov    %ax,%cx
    1354:	66 e8 6a 00          	callw  0x13c2
    1358:	00 00                	add    %al,(%eax)
    135a:	67 66 8d 45 a9       	lea    -0x57(%di),%ax
    135f:	66 89 c1             	mov    %ax,%cx
    1362:	66 e8 5c 00          	callw  0x13c2
    1366:	00 00                	add    %al,(%eax)
    1368:	67 66 8d 45 b8       	lea    -0x48(%di),%ax
    136d:	66 89 c1             	mov    %ax,%cx
    1370:	66 e8 4e 00          	callw  0x13c2
    1374:	00 00                	add    %al,(%eax)
    1376:	67 66 8d 45 c7       	lea    -0x39(%di),%ax
    137b:	66 89 c1             	mov    %ax,%cx
    137e:	66 e8 40 00          	callw  0x13c2
    1382:	00 00                	add    %al,(%eax)
    1384:	67 66 8d 45 d6       	lea    -0x2a(%di),%ax
    1389:	66 89 c1             	mov    %ax,%cx
    138c:	66 e8 32 00          	callw  0x13c2
    1390:	00 00                	add    %al,(%eax)
    1392:	90                   	nop
    1393:	66 c9                	leavew 
    1395:	66 c2 1c 00          	retw   $0x1c
    1399:	90                   	nop
    139a:	90                   	nop
    139b:	90                   	nop
    139c:	66 55                	push   %bp
    139e:	66 89 e5             	mov    %sp,%bp
    13a1:	66 83 ec 04          	sub    $0x4,%sp
    13a5:	67 66 89 4d fc       	mov    %cx,-0x4(%di)
    13aa:	90                   	nop
    13ab:	66 c9                	leavew 
    13ad:	66 c3                	retw   
    13af:	90                   	nop
    13b0:	66 55                	push   %bp
    13b2:	66 89 e5             	mov    %sp,%bp
    13b5:	66 83 ec 04          	sub    $0x4,%sp
    13b9:	67 66 89 4d fc       	mov    %cx,-0x4(%di)
    13be:	90                   	nop
    13bf:	66 c9                	leavew 
    13c1:	66 c3                	retw   
    13c3:	90                   	nop
    13c4:	66 55                	push   %bp
    13c6:	66 89 e5             	mov    %sp,%bp
    13c9:	66 83 ec 04          	sub    $0x4,%sp
    13cd:	67 66 89 4d fc       	mov    %cx,-0x4(%di)
    13d2:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
    13d7:	66 89 c1             	mov    %ax,%cx
    13da:	66 e8 d0 ff          	callw  0x13ae
    13de:	ff                   	(bad)  
    13df:	ff 90 66 c9 66 c3    	call   *-0x3c99369a(%eax)
    13e5:	90                   	nop
    13e6:	66 55                	push   %bp
    13e8:	66 89 e5             	mov    %sp,%bp
    13eb:	66 56                	push   %si
    13ed:	66 53                	push   %bx
    13ef:	66 83 ec 1c          	sub    $0x1c,%sp
    13f3:	67 66 89 4d f4       	mov    %cx,-0xc(%di)
    13f8:	67 66 8b 45 10       	mov    0x10(%di),%ax
    13fd:	67 66 8b 5d 14       	mov    0x14(%di),%bx
    1402:	67 66 8b 4d 18       	mov    0x18(%di),%cx
    1407:	67 66 8b 55 1c       	mov    0x1c(%di),%dx
    140c:	67 66 8b 75 20       	mov    0x20(%di),%si
    1411:	67 66 89 75 dc       	mov    %si,-0x24(%di)
    1416:	67 88 45 f0          	mov    %al,-0x10(%di)
    141a:	67 88 5d ec          	mov    %bl,-0x14(%di)
    141e:	67 88 4d e8          	mov    %cl,-0x18(%di)
    1422:	67 88 55 e4          	mov    %dl,-0x1c(%di)
    1426:	67 66 0f b6 45 dc    	movzbw -0x24(%di),%ax
    142c:	67 88 45 e0          	mov    %al,-0x20(%di)
    1430:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1435:	66 89 c1             	mov    %ax,%cx
    1438:	66 e8 5e ff          	callw  0x139a
    143c:	ff                   	(bad)  
    143d:	ff 67 66             	jmp    *0x66(%edi)
    1440:	8b 45 f4             	mov    -0xc(%ebp),%eax
    1443:	67 c6 40 04 00       	movb   $0x0,0x4(%bx,%si)
    1448:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    144d:	67 66 0f b6 55 e4    	movzbw -0x1c(%di),%dx
    1453:	67 88 50 05          	mov    %dl,0x5(%bx,%si)
    1457:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    145c:	67 c6 40 06 00       	movb   $0x0,0x6(%bx,%si)
    1461:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1466:	67 c6 40 07 00       	movb   $0x0,0x7(%bx,%si)
    146b:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1470:	67 66 0f b6 55 e0    	movzbw -0x20(%di),%dx
    1476:	67 88 50 0b          	mov    %dl,0xb(%bx,%si)
    147a:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    147f:	67 66 0f b6 55 ec    	movzbw -0x14(%di),%dx
    1485:	67 88 50 0c          	mov    %dl,0xc(%bx,%si)
    1489:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    148e:	67 66 0f b6 55 e8    	movzbw -0x18(%di),%dx
    1494:	67 88 50 0d          	mov    %dl,0xd(%bx,%si)
    1498:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    149d:	67 66 0f b6 55 f0    	movzbw -0x10(%di),%dx
    14a3:	67 88 50 0e          	mov    %dl,0xe(%bx,%si)
    14a7:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    14ac:	67 66 8b 55 08       	mov    0x8(%di),%dx
    14b1:	67 66 89 10          	mov    %dx,(%bx,%si)
    14b5:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    14ba:	66 83 c0 08          	add    $0x8,%ax
    14be:	67 66 8b 55 0c       	mov    0xc(%di),%dx
    14c3:	67 89 10             	mov    %edx,(%bx,%si)
    14c6:	67 66 8b 45 0c       	mov    0xc(%di),%ax
    14cb:	66 25 00 00          	and    $0x0,%ax
    14cf:	0f 00 66 c1          	verr   -0x3f(%esi)
    14d3:	f8                   	clc    
    14d4:	10 66 89             	adc    %ah,-0x77(%esi)
    14d7:	c2 67 66             	ret    $0x6667
    14da:	8b 45 f4             	mov    -0xc(%ebp),%eax
    14dd:	67 88 50 0a          	mov    %dl,0xa(%bx,%si)
    14e1:	90                   	nop
    14e2:	66 83 c4 1c          	add    $0x1c,%sp
    14e6:	66 5b                	pop    %bx
    14e8:	66 5e                	pop    %si
    14ea:	66 5d                	pop    %bp
    14ec:	66 c2 1c 00          	retw   $0x1c
    14f0:	66 55                	push   %bp
    14f2:	66 89 e5             	mov    %sp,%bp
    14f5:	66 83 ec 04          	sub    $0x4,%sp
    14f9:	67 66 89 4d fc       	mov    %cx,-0x4(%di)
    14fe:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
    1503:	67 66 8b 10          	mov    (%bx,%si),%dx
    1507:	67 66 8b 45 08       	mov    0x8(%di),%ax
    150c:	67 66 8b 00          	mov    (%bx,%si),%ax
    1510:	66 39 c2             	cmp    %ax,%dx
    1513:	0f 85 0b 01 67 66    	jne    0x66671624
    1519:	8b 45 fc             	mov    -0x4(%ebp),%eax
    151c:	66 83 c0 08          	add    $0x8,%ax
    1520:	67 66 8b 10          	mov    (%bx,%si),%dx
    1524:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1529:	66 83 c0 08          	add    $0x8,%ax
    152d:	67 66 0f b7 00       	movzww (%bx,%si),%ax
    1532:	66 98                	cbtw   
    1534:	66 31 d0             	xor    %dx,%ax
    1537:	66 25 ff ff          	and    $0xffff,%ax
    153b:	0f 00 66 85          	verr   -0x7b(%esi)
    153f:	c0 0f 85             	rorb   $0x85,(%edi)
    1542:	de 00                	fiadd  (%eax)
    1544:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
    1549:	67 66 0f b6 50 0b    	movzbw 0xb(%bx,%si),%dx
    154f:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1554:	67 66 0f b6 40 0b    	movzbw 0xb(%bx,%si),%ax
    155a:	38 c2                	cmp    %al,%dl
    155c:	0f 85 c2 00 67 66    	jne    0x66671624
    1562:	8b 45 fc             	mov    -0x4(%ebp),%eax
    1565:	67 66 0f b6 50 06    	movzbw 0x6(%bx,%si),%dx
    156b:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1570:	67 66 0f b6 40 06    	movzbw 0x6(%bx,%si),%ax
    1576:	38 c2                	cmp    %al,%dl
    1578:	0f 85 a6 00 67 66    	jne    0x66671624
    157e:	8b 45 fc             	mov    -0x4(%ebp),%eax
    1581:	67 66 0f b6 50 05    	movzbw 0x5(%bx,%si),%dx
    1587:	67 66 8b 45 08       	mov    0x8(%di),%ax
    158c:	67 66 0f b6 40 05    	movzbw 0x5(%bx,%si),%ax
    1592:	38 c2                	cmp    %al,%dl
    1594:	0f 85 8a 00 67 66    	jne    0x66671624
    159a:	8b 45 fc             	mov    -0x4(%ebp),%eax
    159d:	67 66 0f b6 50 0d    	movzbw 0xd(%bx,%si),%dx
    15a3:	67 66 8b 45 08       	mov    0x8(%di),%ax
    15a8:	67 66 0f b6 40 0d    	movzbw 0xd(%bx,%si),%ax
    15ae:	38 c2                	cmp    %al,%dl
    15b0:	75 70                	jne    0x1622
    15b2:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
    15b7:	67 66 0f b6 50 0e    	movzbw 0xe(%bx,%si),%dx
    15bd:	67 66 8b 45 08       	mov    0x8(%di),%ax
    15c2:	67 66 0f b6 40 0e    	movzbw 0xe(%bx,%si),%ax
    15c8:	38 c2                	cmp    %al,%dl
    15ca:	75 56                	jne    0x1622
    15cc:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
    15d1:	67 66 0f b6 50 04    	movzbw 0x4(%bx,%si),%dx
    15d7:	67 66 8b 45 08       	mov    0x8(%di),%ax
    15dc:	67 66 0f b6 40 04    	movzbw 0x4(%bx,%si),%ax
    15e2:	38 c2                	cmp    %al,%dl
    15e4:	75 3c                	jne    0x1622
    15e6:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
    15eb:	67 66 0f b6 50 07    	movzbw 0x7(%bx,%si),%dx
    15f1:	67 66 8b 45 08       	mov    0x8(%di),%ax
    15f6:	67 66 0f b6 40 07    	movzbw 0x7(%bx,%si),%ax
    15fc:	38 c2                	cmp    %al,%dl
    15fe:	75 22                	jne    0x1622
    1600:	67 66 8b 45 fc       	mov    -0x4(%di),%ax
    1605:	67 66 0f b6 50 0c    	movzbw 0xc(%bx,%si),%dx
    160b:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1610:	67 66 0f b6 40 0c    	movzbw 0xc(%bx,%si),%ax
    1616:	38 c2                	cmp    %al,%dl
    1618:	75 08                	jne    0x1622
    161a:	66 b8 01 00          	mov    $0x1,%ax
    161e:	00 00                	add    %al,(%eax)
    1620:	eb 06                	jmp    0x1628
    1622:	66 b8 00 00          	mov    $0x0,%ax
    1626:	00 00                	add    %al,(%eax)
    1628:	66 c9                	leavew 
    162a:	66 c2 04 00          	retw   $0x4
    162e:	66 55                	push   %bp
    1630:	66 89 e5             	mov    %sp,%bp
    1633:	66 83 ec 38          	sub    $0x38,%sp
    1637:	67 66 89 4d e4       	mov    %cx,-0x1c(%di)
    163c:	67 66 8b 45 0c       	mov    0xc(%di),%ax
    1641:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    1646:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    164b:	66 83 c0 08          	add    $0x8,%ax
    164f:	67 66 0f b7 00       	movzww (%bx,%si),%ax
    1654:	66 98                	cbtw   
    1656:	66 0f b7 d0          	movzww %ax,%dx
    165a:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    165f:	67 66 89 54 24       	mov    %dx,0x24(%si)
    1664:	08 67 66             	or     %ah,0x66(%edi)
    1667:	89 44 24 04          	mov    %eax,0x4(%esp)
    166b:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1670:	67 66 89 04          	mov    %ax,(%si)
    1674:	24 66                	and    $0x66,%al
    1676:	e8 25 f3 ff ff       	call   0x9a0
    167b:	67 66 83 45 f4 02    	addw   $0x2,-0xc(%di)
    1681:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    1686:	67 66 8b 00          	mov    (%bx,%si),%ax
    168a:	66 0f b7 d0          	movzww %ax,%dx
    168e:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1693:	67 66 89 54 24       	mov    %dx,0x24(%si)
    1698:	08 67 66             	or     %ah,0x66(%edi)
    169b:	89 44 24 04          	mov    %eax,0x4(%esp)
    169f:	67 66 8b 45 08       	mov    0x8(%di),%ax
    16a4:	67 66 89 04          	mov    %ax,(%si)
    16a8:	24 66                	and    $0x66,%al
    16aa:	e8 f1 f2 ff ff       	call   0x9a0
    16af:	67 66 83 45 f4 02    	addw   $0x2,-0xc(%di)
    16b5:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    16ba:	67 66 8b 00          	mov    (%bx,%si),%ax
    16be:	66 25 00 00          	and    $0x0,%ax
    16c2:	ff 00                	incl   (%eax)
    16c4:	66 c1 f8 10          	sar    $0x10,%ax
    16c8:	66 89 c2             	mov    %ax,%dx
    16cb:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    16d0:	67 66 89 54 24       	mov    %dx,0x24(%si)
    16d5:	08 67 66             	or     %ah,0x66(%edi)
    16d8:	89 44 24 04          	mov    %eax,0x4(%esp)
    16dc:	67 66 8b 45 08       	mov    0x8(%di),%ax
    16e1:	67 66 89 04          	mov    %ax,(%si)
    16e5:	24 66                	and    $0x66,%al
    16e7:	e8 7a f2 ff ff       	call   0x966
    16ec:	67 66 83 45 f4 01    	addw   $0x1,-0xc(%di)
    16f2:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    16f7:	67 66 0f b6 40 0b    	movzbw 0xb(%bx,%si),%ax
    16fd:	66 0f be c0          	movsbw %al,%ax
    1701:	66 c1 e0 07          	shl    $0x7,%ax
    1705:	66 0f b6 d0          	movzbw %al,%dx
    1709:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    170e:	67 66 0f b6 40 0c    	movzbw 0xc(%bx,%si),%ax
    1714:	66 0f be c0          	movsbw %al,%ax
    1718:	66 83 e0 03          	and    $0x3,%ax
    171c:	66 c1 e0 05          	shl    $0x5,%ax
    1720:	66 09 c2             	or     %ax,%dx
    1723:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    1728:	67 66 0f b6 40 0d    	movzbw 0xd(%bx,%si),%ax
    172e:	66 0f be c0          	movsbw %al,%ax
    1732:	66 83 e0 01          	and    $0x1,%ax
    1736:	66 c1 e0 04          	shl    $0x4,%ax
    173a:	66 09 c2             	or     %ax,%dx
    173d:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    1742:	67 66 0f b6 40 0e    	movzbw 0xe(%bx,%si),%ax
    1748:	66 0f be c0          	movsbw %al,%ax
    174c:	66 83 e0 0f          	and    $0xf,%ax
    1750:	66 09 c2             	or     %ax,%dx
    1753:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1758:	67 66 89 54 24       	mov    %dx,0x24(%si)
    175d:	08 67 66             	or     %ah,0x66(%edi)
    1760:	89 44 24 04          	mov    %eax,0x4(%esp)
    1764:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1769:	67 66 89 04          	mov    %ax,(%si)
    176d:	24 66                	and    $0x66,%al
    176f:	e8 f2 f1 ff ff       	call   0x966
    1774:	67 66 83 45 f4 01    	addw   $0x1,-0xc(%di)
    177a:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    177f:	67 66 0f b6 40 04    	movzbw 0x4(%bx,%si),%ax
    1785:	66 0f be c0          	movsbw %al,%ax
    1789:	66 c1 e0 07          	shl    $0x7,%ax
    178d:	66 0f b6 d0          	movzbw %al,%dx
    1791:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    1796:	67 66 0f b6 40 05    	movzbw 0x5(%bx,%si),%ax
    179c:	66 0f be c0          	movsbw %al,%ax
    17a0:	66 83 e0 01          	and    $0x1,%ax
    17a4:	66 c1 e0 06          	shl    $0x6,%ax
    17a8:	66 09 c2             	or     %ax,%dx
    17ab:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    17b0:	67 66 0f b6 40 06    	movzbw 0x6(%bx,%si),%ax
    17b6:	66 0f be c0          	movsbw %al,%ax
    17ba:	66 83 e0 01          	and    $0x1,%ax
    17be:	66 c1 e0 05          	shl    $0x5,%ax
    17c2:	66 09 c2             	or     %ax,%dx
    17c5:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    17ca:	67 66 0f b6 40 07    	movzbw 0x7(%bx,%si),%ax
    17d0:	66 0f be c0          	movsbw %al,%ax
    17d4:	66 83 e0 01          	and    $0x1,%ax
    17d8:	66 c1 e0 04          	shl    $0x4,%ax
    17dc:	66 09 c2             	or     %ax,%dx
    17df:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    17e4:	66 83 c0 08          	add    $0x8,%ax
    17e8:	67 66 8b 00          	mov    (%bx,%si),%ax
    17ec:	66 25 00 00          	and    $0x0,%ax
    17f0:	0f 00 66 c1          	verr   -0x3f(%esi)
    17f4:	f8                   	clc    
    17f5:	10 66 09             	adc    %ah,0x9(%esi)
    17f8:	c2 67 66             	ret    $0x6667
    17fb:	8b 45 f4             	mov    -0xc(%ebp),%eax
    17fe:	67 66 89 54 24       	mov    %dx,0x24(%si)
    1803:	08 67 66             	or     %ah,0x66(%edi)
    1806:	89 44 24 04          	mov    %eax,0x4(%esp)
    180a:	67 66 8b 45 08       	mov    0x8(%di),%ax
    180f:	67 66 89 04          	mov    %ax,(%si)
    1813:	24 66                	and    $0x66,%al
    1815:	e8 4c f1 ff ff       	call   0x966
    181a:	67 66 83 45 f4 01    	addw   $0x1,-0xc(%di)
    1820:	67 66 8b 45 e4       	mov    -0x1c(%di),%ax
    1825:	67 66 8b 00          	mov    (%bx,%si),%ax
    1829:	66 c1 e8 18          	shr    $0x18,%ax
    182d:	66 89 c2             	mov    %ax,%dx
    1830:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1835:	67 66 89 54 24       	mov    %dx,0x24(%si)
    183a:	08 67 66             	or     %ah,0x66(%edi)
    183d:	89 44 24 04          	mov    %eax,0x4(%esp)
    1841:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1846:	67 66 89 04          	mov    %ax,(%si)
    184a:	24 66                	and    $0x66,%al
    184c:	e8 15 f1 ff ff       	call   0x966
    1851:	67 66 83 45 f4 01    	addw   $0x1,-0xc(%di)
    1857:	90                   	nop
    1858:	66 c9                	leavew 
    185a:	66 c2 08 00          	retw   $0x8
    185e:	66 55                	push   %bp
    1860:	66 89 e5             	mov    %sp,%bp
    1863:	66 83 ec 28          	sub    $0x28,%sp
    1867:	67 66 8b 45 08       	mov    0x8(%di),%ax
    186c:	66 83 c0 08          	add    $0x8,%ax
    1870:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    1875:	67 66 8b 45 10       	mov    0x10(%di),%ax
    187a:	67 66 89 45 f0       	mov    %ax,-0x10(%di)
    187f:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    1884:	67 66 89 44 24       	mov    %ax,0x24(%si)
    1889:	04 67                	add    $0x67,%al
    188b:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    188f:	67 66 89 04          	mov    %ax,(%si)
    1893:	24 66                	and    $0x66,%al
    1895:	e8 7c f0 ff ff       	call   0x916
    189a:	66 89 c2             	mov    %ax,%dx
    189d:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    18a2:	67 89 10             	mov    %edx,(%bx,%si)
    18a5:	67 66 83 45 f0 02    	addw   $0x2,-0x10(%di)
    18ab:	67 66 8b 45 08       	mov    0x8(%di),%ax
    18b0:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    18b5:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    18ba:	67 66 89 44 24       	mov    %ax,0x24(%si)
    18bf:	04 67                	add    $0x67,%al
    18c1:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    18c5:	67 66 89 04          	mov    %ax,(%si)
    18c9:	24 66                	and    $0x66,%al
    18cb:	e8 46 f0 ff ff       	call   0x916
    18d0:	66 89 c2             	mov    %ax,%dx
    18d3:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    18d8:	67 89 10             	mov    %edx,(%bx,%si)
    18db:	67 66 83 45 f0 02    	addw   $0x2,-0x10(%di)
    18e1:	67 66 8b 45 08       	mov    0x8(%di),%ax
    18e6:	66 83 c0 02          	add    $0x2,%ax
    18ea:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    18ef:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    18f4:	67 66 89 44 24       	mov    %ax,0x24(%si)
    18f9:	04 67                	add    $0x67,%al
    18fb:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    18ff:	67 66 89 04          	mov    %ax,(%si)
    1903:	24 66                	and    $0x66,%al
    1905:	e8 0c f0 ff ff       	call   0x916
    190a:	66 89 c2             	mov    %ax,%dx
    190d:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1912:	67 88 10             	mov    %dl,(%bx,%si)
    1915:	67 66 83 45 f0 01    	addw   $0x1,-0x10(%di)
    191b:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1920:	67 66 0f b6 40 0e    	movzbw 0xe(%bx,%si),%ax
    1926:	66 0f be c0          	movsbw %al,%ax
    192a:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    192f:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    1934:	67 66 89 44 24       	mov    %ax,0x24(%si)
    1939:	04 67                	add    $0x67,%al
    193b:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    193f:	67 66 89 04          	mov    %ax,(%si)
    1943:	24 66                	and    $0x66,%al
    1945:	e8 cc ef ff ff       	call   0x916
    194a:	66 83 e0 0f          	and    $0xf,%ax
    194e:	66 89 c2             	mov    %ax,%dx
    1951:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1956:	67 88 10             	mov    %dl,(%bx,%si)
    1959:	67 66 8b 45 08       	mov    0x8(%di),%ax
    195e:	67 66 0f b6 40 0d    	movzbw 0xd(%bx,%si),%ax
    1964:	66 0f be c0          	movsbw %al,%ax
    1968:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    196d:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    1972:	67 66 89 44 24       	mov    %ax,0x24(%si)
    1977:	04 67                	add    $0x67,%al
    1979:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    197d:	67 66 89 04          	mov    %ax,(%si)
    1981:	24 66                	and    $0x66,%al
    1983:	e8 8e ef ff ff       	call   0x916
    1988:	66 83 e0 10          	and    $0x10,%ax
    198c:	66 c1 f8 04          	sar    $0x4,%ax
    1990:	66 89 c2             	mov    %ax,%dx
    1993:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1998:	67 88 10             	mov    %dl,(%bx,%si)
    199b:	67 66 8b 45 08       	mov    0x8(%di),%ax
    19a0:	67 66 0f b6 40 0c    	movzbw 0xc(%bx,%si),%ax
    19a6:	66 0f be c0          	movsbw %al,%ax
    19aa:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    19af:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    19b4:	67 66 89 44 24       	mov    %ax,0x24(%si)
    19b9:	04 67                	add    $0x67,%al
    19bb:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    19bf:	67 66 89 04          	mov    %ax,(%si)
    19c3:	24 66                	and    $0x66,%al
    19c5:	e8 4c ef ff ff       	call   0x916
    19ca:	66 83 e0 60          	and    $0x60,%ax
    19ce:	66 c1 f8 05          	sar    $0x5,%ax
    19d2:	66 89 c2             	mov    %ax,%dx
    19d5:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    19da:	67 88 10             	mov    %dl,(%bx,%si)
    19dd:	67 66 8b 45 08       	mov    0x8(%di),%ax
    19e2:	67 66 0f b6 40 0b    	movzbw 0xb(%bx,%si),%ax
    19e8:	66 0f be c0          	movsbw %al,%ax
    19ec:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    19f1:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    19f6:	67 66 89 44 24       	mov    %ax,0x24(%si)
    19fb:	04 67                	add    $0x67,%al
    19fd:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    1a01:	67 66 89 04          	mov    %ax,(%si)
    1a05:	24 66                	and    $0x66,%al
    1a07:	e8 0a ef ff ff       	call   0x916
    1a0c:	66 25 80 00          	and    $0x80,%ax
    1a10:	00 00                	add    %al,(%eax)
    1a12:	66 c1 f8 07          	sar    $0x7,%ax
    1a16:	66 89 c2             	mov    %ax,%dx
    1a19:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1a1e:	67 88 10             	mov    %dl,(%bx,%si)
    1a21:	67 66 83 45 f0 01    	addw   $0x1,-0x10(%di)
    1a27:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1a2c:	66 83 c0 08          	add    $0x8,%ax
    1a30:	66 83 c0 02          	add    $0x2,%ax
    1a34:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    1a39:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    1a3e:	67 66 89 44 24       	mov    %ax,0x24(%si)
    1a43:	04 67                	add    $0x67,%al
    1a45:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    1a49:	67 66 89 04          	mov    %ax,(%si)
    1a4d:	24 66                	and    $0x66,%al
    1a4f:	e8 c2 ee ff ff       	call   0x916
    1a54:	66 83 e0 0f          	and    $0xf,%ax
    1a58:	66 89 c2             	mov    %ax,%dx
    1a5b:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1a60:	67 88 10             	mov    %dl,(%bx,%si)
    1a63:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1a68:	67 66 0f b6 40 07    	movzbw 0x7(%bx,%si),%ax
    1a6e:	66 0f be c0          	movsbw %al,%ax
    1a72:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    1a77:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    1a7c:	67 66 89 44 24       	mov    %ax,0x24(%si)
    1a81:	04 67                	add    $0x67,%al
    1a83:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    1a87:	67 66 89 04          	mov    %ax,(%si)
    1a8b:	24 66                	and    $0x66,%al
    1a8d:	e8 84 ee ff ff       	call   0x916
    1a92:	66 83 e0 10          	and    $0x10,%ax
    1a96:	66 c1 f8 04          	sar    $0x4,%ax
    1a9a:	66 89 c2             	mov    %ax,%dx
    1a9d:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1aa2:	67 88 10             	mov    %dl,(%bx,%si)
    1aa5:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1aaa:	67 66 0f b6 40 06    	movzbw 0x6(%bx,%si),%ax
    1ab0:	66 0f be c0          	movsbw %al,%ax
    1ab4:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    1ab9:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    1abe:	67 66 89 44 24       	mov    %ax,0x24(%si)
    1ac3:	04 67                	add    $0x67,%al
    1ac5:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    1ac9:	67 66 89 04          	mov    %ax,(%si)
    1acd:	24 66                	and    $0x66,%al
    1acf:	e8 42 ee ff ff       	call   0x916
    1ad4:	66 83 e0 20          	and    $0x20,%ax
    1ad8:	66 c1 f8 05          	sar    $0x5,%ax
    1adc:	66 89 c2             	mov    %ax,%dx
    1adf:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1ae4:	67 88 10             	mov    %dl,(%bx,%si)
    1ae7:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1aec:	67 66 0f b6 40 05    	movzbw 0x5(%bx,%si),%ax
    1af2:	66 0f be c0          	movsbw %al,%ax
    1af6:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    1afb:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    1b00:	67 66 89 44 24       	mov    %ax,0x24(%si)
    1b05:	04 67                	add    $0x67,%al
    1b07:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    1b0b:	67 66 89 04          	mov    %ax,(%si)
    1b0f:	24 66                	and    $0x66,%al
    1b11:	e8 00 ee ff ff       	call   0x916
    1b16:	66 83 e0 40          	and    $0x40,%ax
    1b1a:	66 c1 f8 06          	sar    $0x6,%ax
    1b1e:	66 89 c2             	mov    %ax,%dx
    1b21:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1b26:	67 88 10             	mov    %dl,(%bx,%si)
    1b29:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1b2e:	67 66 0f b6 40 04    	movzbw 0x4(%bx,%si),%ax
    1b34:	66 0f be c0          	movsbw %al,%ax
    1b38:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    1b3d:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    1b42:	67 66 89 44 24       	mov    %ax,0x24(%si)
    1b47:	04 67                	add    $0x67,%al
    1b49:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    1b4d:	67 66 89 04          	mov    %ax,(%si)
    1b51:	24 66                	and    $0x66,%al
    1b53:	e8 be ed ff ff       	call   0x916
    1b58:	66 25 80 00          	and    $0x80,%ax
    1b5c:	00 00                	add    %al,(%eax)
    1b5e:	66 c1 f8 07          	sar    $0x7,%ax
    1b62:	66 89 c2             	mov    %ax,%dx
    1b65:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1b6a:	67 88 10             	mov    %dl,(%bx,%si)
    1b6d:	67 66 83 45 f0 01    	addw   $0x1,-0x10(%di)
    1b73:	67 66 8b 45 08       	mov    0x8(%di),%ax
    1b78:	66 83 c0 03          	add    $0x3,%ax
    1b7c:	67 66 89 45 f4       	mov    %ax,-0xc(%di)
    1b81:	67 66 8b 45 f0       	mov    -0x10(%di),%ax
    1b86:	67 66 89 44 24       	mov    %ax,0x24(%si)
    1b8b:	04 67                	add    $0x67,%al
    1b8d:	66 8b 45 0c          	mov    0xc(%ebp),%ax
    1b91:	67 66 89 04          	mov    %ax,(%si)
    1b95:	24 66                	and    $0x66,%al
    1b97:	e8 7a ed ff ff       	call   0x916
    1b9c:	66 89 c2             	mov    %ax,%dx
    1b9f:	67 66 8b 45 f4       	mov    -0xc(%di),%ax
    1ba4:	67 88 10             	mov    %dl,(%bx,%si)
    1ba7:	67 66 83 45 f0 01    	addw   $0x1,-0x10(%di)
    1bad:	67 66 83 45 f4 01    	addw   $0x1,-0xc(%di)
    1bb3:	90                   	nop
    1bb4:	66 c9                	leavew 
    1bb6:	66 c3                	retw   
    1bb8:	66 55                	push   %bp
    1bba:	66 89 e5             	mov    %sp,%bp
    1bbd:	66 53                	push   %bx
    1bbf:	66 83 ec 34          	sub    $0x34,%sp
    1bc3:	67 66 89 4d f8       	mov    %cx,-0x8(%di)
    1bc8:	67 66 8b 55 10       	mov    0x10(%di),%dx
    1bcd:	67 66 8b 45 14       	mov    0x14(%di),%ax
    1bd2:	67 66 89 45 d4       	mov    %ax,-0x2c(%di)
    1bd7:	67 66 8b 5d 18       	mov    0x18(%di),%bx
    1bdc:	67 66 89 5d d0       	mov    %bx,-0x30(%di)
    1be1:	67 66 8b 4d 1c       	mov    0x1c(%di),%cx
    1be6:	67 66 89 4d cc       	mov    %cx,-0x34(%di)
    1beb:	67 66 8b 45 20       	mov    0x20(%di),%ax
    1bf0:	67 66 89 45 c8       	mov    %ax,-0x38(%di)
    1bf5:	67 66 8b 5d 24       	mov    0x24(%di),%bx
    1bfa:	67 66 8b 4d 28       	mov    0x28(%di),%cx
    1bff:	67 66 8b 45 2c       	mov    0x2c(%di),%ax
    1c04:	67 88 55 f4          	mov    %dl,-0xc(%di)
    1c08:	67 66 0f b6 55 d4    	movzbw -0x2c(%di),%dx
    1c0e:	67 88 55 f0          	mov    %dl,-0x10(%di)
    1c12:	67 66 0f b6 55 d0    	movzbw -0x30(%di),%dx
    1c18:	67 88 55 ec          	mov    %dl,-0x14(%di)
    1c1c:	67 66 0f b6 55 cc    	movzbw -0x34(%di),%dx
    1c22:	67 88 55 e8          	mov    %dl,-0x18(%di)
    1c26:	67 66 0f b6 55 c8    	movzbw -0x38(%di),%dx
    1c2c:	67 88 55 e4          	mov    %dl,-0x1c(%di)
    1c30:	67 88 5d e0          	mov    %bl,-0x20(%di)
    1c34:	67 88 4d dc          	mov    %cl,-0x24(%di)
    1c38:	67 88 45 d8          	mov    %al,-0x28(%di)
    1c3c:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
    1c41:	67 66 8b 55 08       	mov    0x8(%di),%dx
    1c46:	67 66 89 10          	mov    %dx,(%bx,%si)
    1c4a:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
    1c4f:	66 83 c0 08          	add    $0x8,%ax
    1c53:	67 66 8b 55 0c       	mov    0xc(%di),%dx
    1c58:	67 89 10             	mov    %edx,(%bx,%si)
    1c5b:	67 66 8b 45 0c       	mov    0xc(%di),%ax
    1c60:	66 25 00 00          	and    $0x0,%ax
    1c64:	0f 00 66 c1          	verr   -0x3f(%esi)
    1c68:	f8                   	clc    
    1c69:	10 66 89             	adc    %ah,-0x77(%esi)
    1c6c:	c2 67 66             	ret    $0x6667
    1c6f:	8b 45 f8             	mov    -0x8(%ebp),%eax
    1c72:	67 88 50 0a          	mov    %dl,0xa(%bx,%si)
    1c76:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
    1c7b:	67 66 0f b6 55 f4    	movzbw -0xc(%di),%dx
    1c81:	67 88 50 0e          	mov    %dl,0xe(%bx,%si)
    1c85:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
    1c8a:	67 66 0f b6 55 f0    	movzbw -0x10(%di),%dx
    1c90:	67 88 50 0c          	mov    %dl,0xc(%bx,%si)
    1c94:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
    1c99:	67 66 0f b6 55 ec    	movzbw -0x14(%di),%dx
    1c9f:	67 88 50 0d          	mov    %dl,0xd(%bx,%si)
    1ca3:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
    1ca8:	67 66 0f b6 55 e8    	movzbw -0x18(%di),%dx
    1cae:	67 88 50 05          	mov    %dl,0x5(%bx,%si)
    1cb2:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
    1cb7:	67 66 0f b6 55 e4    	movzbw -0x1c(%di),%dx
    1cbd:	67 88 50 0b          	mov    %dl,0xb(%bx,%si)
    1cc1:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
    1cc6:	67 66 0f b6 55 e0    	movzbw -0x20(%di),%dx
    1ccc:	67 88 50 04          	mov    %dl,0x4(%bx,%si)
    1cd0:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
    1cd5:	67 66 0f b6 55 dc    	movzbw -0x24(%di),%dx
    1cdb:	67 88 50 06          	mov    %dl,0x6(%bx,%si)
    1cdf:	67 66 8b 45 f8       	mov    -0x8(%di),%ax
    1ce4:	67 66 0f b6 55 d8    	movzbw -0x28(%di),%dx
    1cea:	67 88 50 07          	mov    %dl,0x7(%bx,%si)
    1cee:	90                   	nop
    1cef:	66 83 c4 34          	add    $0x34,%sp
    1cf3:	66 5b                	pop    %bx
    1cf5:	66 5d                	pop    %bp
    1cf7:	66 c2 28 00          	retw   $0x28
    1cfb:	90                   	nop
    1cfc:	00 b8 00 00 80 00    	add    %bh,0x800000(%eax)
    1d02:	00 00                	add    %al,(%eax)
    1d04:	00 00                	add    %al,(%eax)
    1d06:	00 00                	add    %al,(%eax)
    1d08:	20 00                	and    %al,(%eax)
    1d0a:	00 00                	add    %al,(%eax)
    1d0c:	10 00                	adc    %al,(%eax)
    1d0e:	00 00                	add    %al,(%eax)
    1d10:	08 00                	or     %al,(%eax)
    1d12:	00 00                	add    %al,(%eax)
    1d14:	38 00                	cmp    %al,(%eax)
    1d16:	00 00                	add    %al,(%eax)
    1d18:	30 00                	xor    %al,(%eax)
    1d1a:	00 00                	add    %al,(%eax)
    1d1c:	28 00                	sub    %al,(%eax)
    1d1e:	00 00                	add    %al,(%eax)
    1d20:	18 00                	sbb    %al,(%eax)
    1d22:	00 00                	add    %al,(%eax)
    1d24:	00 00                	add    %al,(%eax)
    1d26:	00 00                	add    %al,(%eax)
    1d28:	04 00                	add    $0x0,%al
    1d2a:	00 00                	add    %al,(%eax)
    1d2c:	02 00                	add    (%eax),%al
    1d2e:	00 00                	add    %al,(%eax)
    1d30:	01 00                	add    %eax,(%eax)
    1d32:	00 00                	add    %al,(%eax)
    1d34:	07                   	pop    %es
    1d35:	00 00                	add    %al,(%eax)
    1d37:	00 06                	add    %al,(%esi)
    1d39:	00 00                	add    %al,(%eax)
    1d3b:	00 05 00 00 00 03    	add    %al,0x3000000
    1d41:	00 00                	add    %al,(%eax)
    1d43:	00 00                	add    %al,(%eax)
    1d45:	00 00                	add    %al,(%eax)
    1d47:	00 07                	add    %al,(%edi)
    1d49:	00 00                	add    %al,(%eax)
    1d4b:	00 19                	add    %bl,(%ecx)
    1d4d:	00 00                	add    %al,(%eax)
    1d4f:	00 50 00             	add    %dl,0x0(%eax)
    1d52:	00 00                	add    %al,(%eax)
    1d54:	3e 3e 3e 49          	ds ds ds dec %ecx
    1d58:	6e                   	outsb  %ds:(%esi),(%dx)
    1d59:	69 74 00 3e 3e 3e 44 	imul   $0x65443e3e,0x3e(%eax,%eax,1),%esi
    1d60:	65 
    1d61:	73 74                	jae    0x1dd7
    1d63:	72 6f                	jb     0x1dd4
    1d65:	79 00                	jns    0x1d67
    1d67:	3e 3e 3e 74 65       	ds ds je,pt 0x1dd1
    1d6c:	73 74                	jae    0x1de2
    1d6e:	00 00                	add    %al,(%eax)
    1d70:	02 00                	add    (%eax),%al
    1d72:	00 00                	add    %al,(%eax)
    1d74:	06                   	push   %es
    1d75:	00 00                	add    %al,(%eax)
    1d77:	00 02                	add    %al,(%edx)
    1d79:	00 00                	add    %al,(%eax)
    1d7b:	00 0a                	add    %cl,(%edx)
    1d7d:	00 00                	add    %al,(%eax)
    1d7f:	00 0e                	add    %cl,(%esi)
    1d81:	00 00                	add    %al,(%eax)
    1d83:	00 00                	add    %al,(%eax)
    1d85:	00 00                	add    %al,(%eax)
    1d87:	00 08                	add    %cl,(%eax)
    1d89:	00 00                	add    %al,(%eax)
    1d8b:	00 0a                	add    %cl,(%edx)
    1d8d:	00 00                	add    %al,(%eax)
    1d8f:	00 0d 00 00 00 01    	add    %cl,0x1000000
    1d95:	00 00                	add    %al,(%eax)
    1d97:	00 03                	add    %al,(%ebx)
    1d99:	00 00                	add    %al,(%eax)
    1d9b:	00 09                	add    %cl,(%ecx)
    1d9d:	00 00                	add    %al,(%eax)
    1d9f:	00 0b                	add    %cl,(%ebx)
    1da1:	00 00                	add    %al,(%eax)
    1da3:	00 04 00             	add    %al,(%eax,%eax,1)
    1da6:	00 00                	add    %al,(%eax)
    1da8:	0c 00                	or     $0x0,%al
    1daa:	00 00                	add    %al,(%eax)
    1dac:	05 00 00 00 06       	add    $0x6000000,%eax
    1db1:	00 00                	add    %al,(%eax)
    1db3:	00 07                	add    %al,(%edi)
    1db5:	00 00                	add    %al,(%eax)
    1db7:	00 0e                	add    %cl,(%esi)
    1db9:	00 00                	add    %al,(%eax)
    1dbb:	00 0f                	add    %cl,(%edi)
    1dbd:	00 00                	add    %al,(%eax)
    1dbf:	00 00                	add    %al,(%eax)
    1dc1:	00 00                	add    %al,(%eax)
    1dc3:	00 01                	add    %al,(%ecx)
    1dc5:	00 00                	add    %al,(%eax)
    1dc7:	00 02                	add    %al,(%edx)
    1dc9:	00 00                	add    %al,(%eax)
    1dcb:	00 03                	add    %al,(%ebx)
	...
    1dd5:	00 00                	add    %al,(%eax)
    1dd7:	00 66 90             	add    %ah,-0x70(%esi)
    1dda:	66 90                	xchg   %ax,%ax
    1ddc:	66 90                	xchg   %ax,%ax
    1dde:	66 90                	xchg   %ax,%ax
    1de0:	66 90                	xchg   %ax,%ax
    1de2:	66 90                	xchg   %ax,%ax
    1de4:	66 90                	xchg   %ax,%ax
    1de6:	66 90                	xchg   %ax,%ax
    1de8:	66 90                	xchg   %ax,%ax
    1dea:	66 90                	xchg   %ax,%ax
    1dec:	66 90                	xchg   %ax,%ax
    1dee:	66 90                	xchg   %ax,%ax
    1df0:	66 90                	xchg   %ax,%ax
    1df2:	66 90                	xchg   %ax,%ax
    1df4:	66 90                	xchg   %ax,%ax
    1df6:	66 90                	xchg   %ax,%ax
    1df8:	66 90                	xchg   %ax,%ax
    1dfa:	66 90                	xchg   %ax,%ax
    1dfc:	66 90                	xchg   %ax,%ax
    1dfe:	66 90                	xchg   %ax,%ax
    1e00:	66 90                	xchg   %ax,%ax
    1e02:	66 90                	xchg   %ax,%ax
    1e04:	66 90                	xchg   %ax,%ax
    1e06:	66 90                	xchg   %ax,%ax
    1e08:	66 90                	xchg   %ax,%ax
    1e0a:	66 90                	xchg   %ax,%ax
    1e0c:	66 90                	xchg   %ax,%ax
    1e0e:	66 90                	xchg   %ax,%ax
    1e10:	66 90                	xchg   %ax,%ax
    1e12:	66 90                	xchg   %ax,%ax
    1e14:	66 90                	xchg   %ax,%ax
    1e16:	66 90                	xchg   %ax,%ax
    1e18:	66 90                	xchg   %ax,%ax
    1e1a:	66 90                	xchg   %ax,%ax
    1e1c:	66 90                	xchg   %ax,%ax
    1e1e:	66 90                	xchg   %ax,%ax
    1e20:	66 90                	xchg   %ax,%ax
    1e22:	66 90                	xchg   %ax,%ax
    1e24:	66 90                	xchg   %ax,%ax
    1e26:	66 90                	xchg   %ax,%ax
    1e28:	66 90                	xchg   %ax,%ax
    1e2a:	66 90                	xchg   %ax,%ax
    1e2c:	66 90                	xchg   %ax,%ax
    1e2e:	66 90                	xchg   %ax,%ax
    1e30:	66 90                	xchg   %ax,%ax
    1e32:	66 90                	xchg   %ax,%ax
    1e34:	66 90                	xchg   %ax,%ax
    1e36:	66 90                	xchg   %ax,%ax
    1e38:	66 90                	xchg   %ax,%ax
    1e3a:	66 90                	xchg   %ax,%ax
    1e3c:	66 90                	xchg   %ax,%ax
    1e3e:	66 90                	xchg   %ax,%ax
    1e40:	66 90                	xchg   %ax,%ax
    1e42:	66 90                	xchg   %ax,%ax
    1e44:	66 90                	xchg   %ax,%ax
    1e46:	66 90                	xchg   %ax,%ax
    1e48:	66 90                	xchg   %ax,%ax
    1e4a:	66 90                	xchg   %ax,%ax
    1e4c:	66 90                	xchg   %ax,%ax
    1e4e:	66 90                	xchg   %ax,%ax
    1e50:	66 90                	xchg   %ax,%ax
    1e52:	66 90                	xchg   %ax,%ax
    1e54:	66 90                	xchg   %ax,%ax
    1e56:	66 90                	xchg   %ax,%ax
    1e58:	66 90                	xchg   %ax,%ax
    1e5a:	66 90                	xchg   %ax,%ax
    1e5c:	66 90                	xchg   %ax,%ax
    1e5e:	66 90                	xchg   %ax,%ax
    1e60:	66 90                	xchg   %ax,%ax
    1e62:	66 90                	xchg   %ax,%ax
    1e64:	66 90                	xchg   %ax,%ax
    1e66:	66 90                	xchg   %ax,%ax
    1e68:	66 90                	xchg   %ax,%ax
    1e6a:	66 90                	xchg   %ax,%ax
    1e6c:	66 90                	xchg   %ax,%ax
    1e6e:	66 90                	xchg   %ax,%ax
    1e70:	66 90                	xchg   %ax,%ax
    1e72:	66 90                	xchg   %ax,%ax
    1e74:	66 90                	xchg   %ax,%ax
    1e76:	66 90                	xchg   %ax,%ax
    1e78:	66 90                	xchg   %ax,%ax
    1e7a:	66 90                	xchg   %ax,%ax
    1e7c:	66 90                	xchg   %ax,%ax
    1e7e:	66 90                	xchg   %ax,%ax
    1e80:	66 90                	xchg   %ax,%ax
    1e82:	66 90                	xchg   %ax,%ax
    1e84:	66 90                	xchg   %ax,%ax
    1e86:	66 90                	xchg   %ax,%ax
    1e88:	66 90                	xchg   %ax,%ax
    1e8a:	66 90                	xchg   %ax,%ax
    1e8c:	66 90                	xchg   %ax,%ax
    1e8e:	66 90                	xchg   %ax,%ax
    1e90:	66 90                	xchg   %ax,%ax
    1e92:	66 90                	xchg   %ax,%ax
    1e94:	66 90                	xchg   %ax,%ax
    1e96:	66 90                	xchg   %ax,%ax
    1e98:	66 90                	xchg   %ax,%ax
    1e9a:	66 90                	xchg   %ax,%ax
    1e9c:	66 90                	xchg   %ax,%ax
    1e9e:	66 90                	xchg   %ax,%ax
    1ea0:	66 90                	xchg   %ax,%ax
    1ea2:	66 90                	xchg   %ax,%ax
    1ea4:	66 90                	xchg   %ax,%ax
    1ea6:	66 90                	xchg   %ax,%ax
    1ea8:	66 90                	xchg   %ax,%ax
    1eaa:	66 90                	xchg   %ax,%ax
    1eac:	66 90                	xchg   %ax,%ax
    1eae:	66 90                	xchg   %ax,%ax
    1eb0:	66 90                	xchg   %ax,%ax
    1eb2:	66 90                	xchg   %ax,%ax
    1eb4:	66 90                	xchg   %ax,%ax
    1eb6:	66 90                	xchg   %ax,%ax
    1eb8:	66 90                	xchg   %ax,%ax
    1eba:	66 90                	xchg   %ax,%ax
    1ebc:	66 90                	xchg   %ax,%ax
    1ebe:	66 90                	xchg   %ax,%ax
    1ec0:	66 90                	xchg   %ax,%ax
    1ec2:	66 90                	xchg   %ax,%ax
    1ec4:	66 90                	xchg   %ax,%ax
    1ec6:	66 90                	xchg   %ax,%ax
    1ec8:	66 90                	xchg   %ax,%ax
    1eca:	66 90                	xchg   %ax,%ax
    1ecc:	66 90                	xchg   %ax,%ax
    1ece:	66 90                	xchg   %ax,%ax
    1ed0:	66 90                	xchg   %ax,%ax
    1ed2:	66 90                	xchg   %ax,%ax
    1ed4:	66 90                	xchg   %ax,%ax
    1ed6:	66 90                	xchg   %ax,%ax
    1ed8:	66 90                	xchg   %ax,%ax
    1eda:	66 90                	xchg   %ax,%ax
    1edc:	66 90                	xchg   %ax,%ax
    1ede:	66 90                	xchg   %ax,%ax
    1ee0:	66 90                	xchg   %ax,%ax
    1ee2:	66 90                	xchg   %ax,%ax
    1ee4:	66 90                	xchg   %ax,%ax
    1ee6:	66 90                	xchg   %ax,%ax
    1ee8:	66 90                	xchg   %ax,%ax
    1eea:	66 90                	xchg   %ax,%ax
    1eec:	66 90                	xchg   %ax,%ax
    1eee:	66 90                	xchg   %ax,%ax
    1ef0:	66 90                	xchg   %ax,%ax
    1ef2:	66 90                	xchg   %ax,%ax
    1ef4:	66 90                	xchg   %ax,%ax
    1ef6:	66 90                	xchg   %ax,%ax
    1ef8:	66 90                	xchg   %ax,%ax
    1efa:	66 90                	xchg   %ax,%ax
    1efc:	66 90                	xchg   %ax,%ax
    1efe:	66 90                	xchg   %ax,%ax
    1f00:	66 90                	xchg   %ax,%ax
    1f02:	66 90                	xchg   %ax,%ax
    1f04:	66 90                	xchg   %ax,%ax
    1f06:	66 90                	xchg   %ax,%ax
    1f08:	66 90                	xchg   %ax,%ax
    1f0a:	66 90                	xchg   %ax,%ax
    1f0c:	66 90                	xchg   %ax,%ax
    1f0e:	66 90                	xchg   %ax,%ax
    1f10:	66 90                	xchg   %ax,%ax
    1f12:	66 90                	xchg   %ax,%ax
    1f14:	66 90                	xchg   %ax,%ax
    1f16:	66 90                	xchg   %ax,%ax
    1f18:	66 90                	xchg   %ax,%ax
    1f1a:	66 90                	xchg   %ax,%ax
    1f1c:	66 90                	xchg   %ax,%ax
    1f1e:	66 90                	xchg   %ax,%ax
    1f20:	66 90                	xchg   %ax,%ax
    1f22:	66 90                	xchg   %ax,%ax
    1f24:	66 90                	xchg   %ax,%ax
    1f26:	66 90                	xchg   %ax,%ax
    1f28:	66 90                	xchg   %ax,%ax
    1f2a:	66 90                	xchg   %ax,%ax
    1f2c:	66 90                	xchg   %ax,%ax
    1f2e:	66 90                	xchg   %ax,%ax
    1f30:	66 90                	xchg   %ax,%ax
    1f32:	66 90                	xchg   %ax,%ax
    1f34:	66 90                	xchg   %ax,%ax
    1f36:	66 90                	xchg   %ax,%ax
    1f38:	66 90                	xchg   %ax,%ax
    1f3a:	66 90                	xchg   %ax,%ax
    1f3c:	66 90                	xchg   %ax,%ax
    1f3e:	66 90                	xchg   %ax,%ax
    1f40:	66 90                	xchg   %ax,%ax
    1f42:	66 90                	xchg   %ax,%ax
    1f44:	66 90                	xchg   %ax,%ax
    1f46:	66 90                	xchg   %ax,%ax
    1f48:	66 90                	xchg   %ax,%ax
    1f4a:	66 90                	xchg   %ax,%ax
    1f4c:	66 90                	xchg   %ax,%ax
    1f4e:	66 90                	xchg   %ax,%ax
    1f50:	66 90                	xchg   %ax,%ax
    1f52:	66 90                	xchg   %ax,%ax
    1f54:	66 90                	xchg   %ax,%ax
    1f56:	66 90                	xchg   %ax,%ax
    1f58:	66 90                	xchg   %ax,%ax
    1f5a:	66 90                	xchg   %ax,%ax
    1f5c:	66 90                	xchg   %ax,%ax
    1f5e:	66 90                	xchg   %ax,%ax
    1f60:	66 90                	xchg   %ax,%ax
    1f62:	66 90                	xchg   %ax,%ax
    1f64:	66 90                	xchg   %ax,%ax
    1f66:	66 90                	xchg   %ax,%ax
    1f68:	66 90                	xchg   %ax,%ax
    1f6a:	66 90                	xchg   %ax,%ax
    1f6c:	66 90                	xchg   %ax,%ax
    1f6e:	66 90                	xchg   %ax,%ax
    1f70:	66 90                	xchg   %ax,%ax
    1f72:	66 90                	xchg   %ax,%ax
    1f74:	66 90                	xchg   %ax,%ax
    1f76:	66 90                	xchg   %ax,%ax
    1f78:	66 90                	xchg   %ax,%ax
    1f7a:	66 90                	xchg   %ax,%ax
    1f7c:	66 90                	xchg   %ax,%ax
    1f7e:	66 90                	xchg   %ax,%ax
    1f80:	66 90                	xchg   %ax,%ax
    1f82:	66 90                	xchg   %ax,%ax
    1f84:	66 90                	xchg   %ax,%ax
    1f86:	66 90                	xchg   %ax,%ax
    1f88:	66 90                	xchg   %ax,%ax
    1f8a:	66 90                	xchg   %ax,%ax
    1f8c:	66 90                	xchg   %ax,%ax
    1f8e:	66 90                	xchg   %ax,%ax
    1f90:	66 90                	xchg   %ax,%ax
    1f92:	66 90                	xchg   %ax,%ax
    1f94:	66 90                	xchg   %ax,%ax
    1f96:	66 90                	xchg   %ax,%ax
    1f98:	66 90                	xchg   %ax,%ax
    1f9a:	66 90                	xchg   %ax,%ax
    1f9c:	66 90                	xchg   %ax,%ax
    1f9e:	66 90                	xchg   %ax,%ax
    1fa0:	66 90                	xchg   %ax,%ax
    1fa2:	66 90                	xchg   %ax,%ax
    1fa4:	66 90                	xchg   %ax,%ax
    1fa6:	66 90                	xchg   %ax,%ax
    1fa8:	66 90                	xchg   %ax,%ax
    1faa:	66 90                	xchg   %ax,%ax
    1fac:	66 90                	xchg   %ax,%ax
    1fae:	66 90                	xchg   %ax,%ax
    1fb0:	66 90                	xchg   %ax,%ax
    1fb2:	66 90                	xchg   %ax,%ax
    1fb4:	66 90                	xchg   %ax,%ax
    1fb6:	66 90                	xchg   %ax,%ax
    1fb8:	66 90                	xchg   %ax,%ax
    1fba:	66 90                	xchg   %ax,%ax
    1fbc:	66 90                	xchg   %ax,%ax
    1fbe:	66 90                	xchg   %ax,%ax
    1fc0:	66 90                	xchg   %ax,%ax
    1fc2:	66 90                	xchg   %ax,%ax
    1fc4:	66 90                	xchg   %ax,%ax
    1fc6:	66 90                	xchg   %ax,%ax
    1fc8:	66 90                	xchg   %ax,%ax
    1fca:	66 90                	xchg   %ax,%ax
    1fcc:	66 90                	xchg   %ax,%ax
    1fce:	66 90                	xchg   %ax,%ax
    1fd0:	66 90                	xchg   %ax,%ax
    1fd2:	66 90                	xchg   %ax,%ax
    1fd4:	66 90                	xchg   %ax,%ax
    1fd6:	66 90                	xchg   %ax,%ax
    1fd8:	66 90                	xchg   %ax,%ax
    1fda:	66 90                	xchg   %ax,%ax
    1fdc:	66 90                	xchg   %ax,%ax
    1fde:	66 90                	xchg   %ax,%ax
    1fe0:	66 90                	xchg   %ax,%ax
    1fe2:	66 90                	xchg   %ax,%ax
    1fe4:	66 90                	xchg   %ax,%ax
    1fe6:	66 90                	xchg   %ax,%ax
    1fe8:	66 90                	xchg   %ax,%ax
    1fea:	66 90                	xchg   %ax,%ax
    1fec:	66 90                	xchg   %ax,%ax
    1fee:	66 90                	xchg   %ax,%ax
    1ff0:	66 90                	xchg   %ax,%ax
    1ff2:	66 90                	xchg   %ax,%ax
    1ff4:	66 90                	xchg   %ax,%ax
    1ff6:	66 90                	xchg   %ax,%ax
    1ff8:	66 90                	xchg   %ax,%ax
    1ffa:	66 90                	xchg   %ax,%ax
    1ffc:	66 90                	xchg   %ax,%ax
    1ffe:	66 90                	xchg   %ax,%ax
	...
    2800:	66 b8 18 00          	mov    $0x18,%ax
    2804:	8e d8                	mov    %eax,%ds
    2806:	8e c0                	mov    %eax,%es
    2808:	8e e8                	mov    %eax,%gs
    280a:	8e e0                	mov    %eax,%fs
    280c:	66 b8 20 00          	mov    $0x20,%ax
    2810:	8e d0                	mov    %eax,%ss
    2812:	bc 00 08 00 00       	mov    $0x800,%esp
    2817:	e8 02 00 00 00       	call   0x281e
    281c:	eb fe                	jmp    0x281c
    281e:	55                   	push   %ebp
    281f:	89 e5                	mov    %esp,%ebp
    2821:	53                   	push   %ebx
    2822:	81 ec e4 00 00 00    	sub    $0xe4,%esp
    2828:	e8 73 06 00 00       	call   0x2ea0
    282d:	a1 6c 1a 00 00       	mov    0x1a6c,%eax
    2832:	89 44 24 04          	mov    %eax,0x4(%esp)
    2836:	c7 04 24 ac 19 00 00 	movl   $0x19ac,(%esp)
    283d:	e8 58 04 00 00       	call   0x2c9a
    2842:	8d 45 88             	lea    -0x78(%ebp),%eax
    2845:	89 c1                	mov    %eax,%ecx
    2847:	e8 ec 0f 00 00       	call   0x3838
    284c:	8d 45 88             	lea    -0x78(%ebp),%eax
    284f:	8d 58 08             	lea    0x8(%eax),%ebx
    2852:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
    2859:	00 
    285a:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
    2861:	00 
    2862:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
    2869:	e8 50 07 00 00       	call   0x2fbe
    286e:	66 89 03             	mov    %ax,(%ebx)
    2871:	8d 45 88             	lea    -0x78(%ebp),%eax
    2874:	83 c0 04             	add    $0x4,%eax
    2877:	c7 00 fc 05 00 00    	movl   $0x5fc,(%eax)
    287d:	8d 45 88             	lea    -0x78(%ebp),%eax
    2880:	c7 44 24 04 00 44 00 	movl   $0x4400,0x4(%esp)
    2887:	00 
    2888:	c7 04 24 00 00 01 00 	movl   $0x10000,(%esp)
    288f:	89 c1                	mov    %eax,%ecx
    2891:	e8 d6 0f 00 00       	call   0x386c
    2896:	83 ec 08             	sub    $0x8,%esp
    2899:	c7 04 24 33 12 00 00 	movl   $0x1233,(%esp)
    28a0:	e8 f9 04 00 00       	call   0x2d9e
    28a5:	a1 6c 1a 00 00       	mov    0x1a6c,%eax
    28aa:	89 44 24 04          	mov    %eax,0x4(%esp)
    28ae:	c7 04 24 c5 19 00 00 	movl   $0x19c5,(%esp)
    28b5:	e8 e0 03 00 00       	call   0x2c9a
    28ba:	a1 c0 1a 00 00       	mov    0x1ac0,%eax
    28bf:	0f be d0             	movsbl %al,%edx
    28c2:	8d 85 79 ff ff ff    	lea    -0x87(%ebp),%eax
    28c8:	c7 44 24 18 01 00 00 	movl   $0x1,0x18(%esp)
    28cf:	00 
    28d0:	c7 44 24 14 00 00 00 	movl   $0x0,0x14(%esp)
    28d7:	00 
    28d8:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
    28df:	00 
    28e0:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
    28e7:	00 
    28e8:	89 54 24 08          	mov    %edx,0x8(%esp)
    28ec:	c7 44 24 04 68 00 00 	movl   $0x68,0x4(%esp)
    28f3:	00 
    28f4:	c7 04 24 00 44 00 00 	movl   $0x4400,(%esp)
    28fb:	89 c1                	mov    %eax,%ecx
    28fd:	e8 34 07 00 00       	call   0x3036
    2902:	83 ec 1c             	sub    $0x1c,%esp
    2905:	8d 85 79 ff ff ff    	lea    -0x87(%ebp),%eax
    290b:	c7 44 24 04 b8 9d 00 	movl   $0x9db8,0x4(%esp)
    2912:	00 
    2913:	c7 04 24 00 00 01 00 	movl   $0x10000,(%esp)
    291a:	89 c1                	mov    %eax,%ecx
    291c:	e8 a7 08 00 00       	call   0x31c8
    2921:	83 ec 08             	sub    $0x8,%esp
    2924:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
    292b:	00 
    292c:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
    2933:	00 
    2934:	c7 04 24 05 00 00 00 	movl   $0x5,(%esp)
    293b:	e8 7e 06 00 00       	call   0x2fbe
    2940:	98                   	cwtl   
    2941:	89 04 24             	mov    %eax,(%esp)
    2944:	e8 6b 06 00 00       	call   0x2fb4
    2949:	a1 6c 1a 00 00       	mov    0x1a6c,%eax
    294e:	89 44 24 04          	mov    %eax,0x4(%esp)
    2952:	c7 04 24 d3 19 00 00 	movl   $0x19d3,(%esp)
    2959:	e8 3c 03 00 00       	call   0x2c9a
    295e:	8d 85 6e ff ff ff    	lea    -0x92(%ebp),%eax
    2964:	89 c1                	mov    %eax,%ecx
    2966:	e8 e9 0c 00 00       	call   0x3654
    296b:	c7 04 24 45 23 01 00 	movl   $0x12345,(%esp)
    2972:	e8 27 04 00 00       	call   0x2d9e
    2977:	8b 0d f0 1a 00 00    	mov    0x1af0,%ecx
    297d:	8b 15 f4 1a 00 00    	mov    0x1af4,%edx
    2983:	bb e3 0b 00 00       	mov    $0xbe3,%ebx
    2988:	8d 85 6e ff ff ff    	lea    -0x92(%ebp),%eax
    298e:	c7 44 24 14 01 00 00 	movl   $0x1,0x14(%esp)
    2995:	00 
    2996:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
    299d:	00 
    299e:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
    29a2:	89 54 24 08          	mov    %edx,0x8(%esp)
    29a6:	89 5c 24 04          	mov    %ebx,0x4(%esp)
    29aa:	c7 04 24 10 00 00 00 	movl   $0x10,(%esp)
    29b1:	89 c1                	mov    %eax,%ecx
    29b3:	e8 92 0d 00 00       	call   0x374a
    29b8:	83 ec 18             	sub    $0x18,%esp
    29bb:	8d 85 6e ff ff ff    	lea    -0x92(%ebp),%eax
    29c1:	c7 44 24 04 20 9d 00 	movl   $0x9d20,0x4(%esp)
    29c8:	00 
    29c9:	c7 04 24 00 00 01 00 	movl   $0x10000,(%esp)
    29d0:	89 c1                	mov    %eax,%ecx
    29d2:	e8 f3 0d 00 00       	call   0x37ca
    29d7:	83 ec 08             	sub    $0x8,%esp
    29da:	a1 6c 1a 00 00       	mov    0x1a6c,%eax
    29df:	bb e2 19 00 00       	mov    $0x19e2,%ebx
    29e4:	b9 00 00 01 00       	mov    $0x10000,%ecx
    29e9:	89 c2                	mov    %eax,%edx
    29eb:	cd 24                	int    $0x24
    29ed:	a1 a0 1a 00 00       	mov    0x1aa0,%eax
    29f2:	0f be d0             	movsbl %al,%edx
    29f5:	8d 85 5f ff ff ff    	lea    -0xa1(%ebp),%eax
    29fb:	c7 44 24 18 01 00 00 	movl   $0x1,0x18(%esp)
    2a02:	00 
    2a03:	c7 44 24 14 01 00 00 	movl   $0x1,0x14(%esp)
    2a0a:	00 
    2a0b:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
    2a12:	00 
    2a13:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
    2a1a:	00 
    2a1b:	89 54 24 08          	mov    %edx,0x8(%esp)
    2a1f:	c7 44 24 04 ff ff 0f 	movl   $0xfffff,0x4(%esp)
    2a26:	00 
    2a27:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
    2a2e:	89 c1                	mov    %eax,%ecx
    2a30:	e8 01 06 00 00       	call   0x3036
    2a35:	83 ec 1c             	sub    $0x1c,%esp
    2a38:	a1 9c 1a 00 00       	mov    0x1a9c,%eax
    2a3d:	0f be d0             	movsbl %al,%edx
    2a40:	8d 85 50 ff ff ff    	lea    -0xb0(%ebp),%eax
    2a46:	c7 44 24 18 01 00 00 	movl   $0x1,0x18(%esp)
    2a4d:	00 
    2a4e:	c7 44 24 14 01 00 00 	movl   $0x1,0x14(%esp)
    2a55:	00 
    2a56:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
    2a5d:	00 
    2a5e:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
    2a65:	00 
    2a66:	89 54 24 08          	mov    %edx,0x8(%esp)
    2a6a:	c7 44 24 04 ff ff 00 	movl   $0xffff,0x4(%esp)
    2a71:	00 
    2a72:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
    2a79:	89 c1                	mov    %eax,%ecx
    2a7b:	e8 b6 05 00 00       	call   0x3036
    2a80:	83 ec 1c             	sub    $0x1c,%esp
    2a83:	a1 94 1a 00 00       	mov    0x1a94,%eax
    2a88:	0f be d0             	movsbl %al,%edx
    2a8b:	8d 85 41 ff ff ff    	lea    -0xbf(%ebp),%eax
    2a91:	c7 44 24 18 01 00 00 	movl   $0x1,0x18(%esp)
    2a98:	00 
    2a99:	c7 44 24 14 01 00 00 	movl   $0x1,0x14(%esp)
    2aa0:	00 
    2aa1:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
    2aa8:	00 
    2aa9:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
    2ab0:	00 
    2ab1:	89 54 24 08          	mov    %edx,0x8(%esp)
    2ab5:	c7 44 24 04 00 08 00 	movl   $0x800,0x4(%esp)
    2abc:	00 
    2abd:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
    2ac4:	89 c1                	mov    %eax,%ecx
    2ac6:	e8 6b 05 00 00       	call   0x3036
    2acb:	83 ec 1c             	sub    $0x1c,%esp
    2ace:	8d 85 5f ff ff ff    	lea    -0xa1(%ebp),%eax
    2ad4:	c7 44 24 04 c0 9d 00 	movl   $0x9dc0,0x4(%esp)
    2adb:	00 
    2adc:	c7 04 24 00 00 01 00 	movl   $0x10000,(%esp)
    2ae3:	89 c1                	mov    %eax,%ecx
    2ae5:	e8 de 06 00 00       	call   0x31c8
    2aea:	83 ec 08             	sub    $0x8,%esp
    2aed:	8d 85 50 ff ff ff    	lea    -0xb0(%ebp),%eax
    2af3:	c7 44 24 04 c8 9d 00 	movl   $0x9dc8,0x4(%esp)
    2afa:	00 
    2afb:	c7 04 24 00 00 01 00 	movl   $0x10000,(%esp)
    2b02:	89 c1                	mov    %eax,%ecx
    2b04:	e8 bf 06 00 00       	call   0x31c8
    2b09:	83 ec 08             	sub    $0x8,%esp
    2b0c:	8d 85 41 ff ff ff    	lea    -0xbf(%ebp),%eax
    2b12:	c7 44 24 04 d0 9d 00 	movl   $0x9dd0,0x4(%esp)
    2b19:	00 
    2b1a:	c7 04 24 00 00 01 00 	movl   $0x10000,(%esp)
    2b21:	89 c1                	mov    %eax,%ecx
    2b23:	e8 a0 06 00 00       	call   0x31c8
    2b28:	83 ec 08             	sub    $0x8,%esp
    2b2b:	a1 6c 1a 00 00       	mov    0x1a6c,%eax
    2b30:	89 44 24 04          	mov    %eax,0x4(%esp)
    2b34:	c7 04 24 f6 19 00 00 	movl   $0x19f6,(%esp)
    2b3b:	e8 5a 01 00 00       	call   0x2c9a
    2b40:	e8 bb 04 00 00       	call   0x3000
    2b45:	ba 6e 0b 00 00       	mov    $0xb6e,%edx
    2b4a:	c7 44 24 10 43 00 00 	movl   $0x43,0x10(%esp)
    2b51:	00 
    2b52:	c7 44 24 0c fc 07 00 	movl   $0x7fc,0xc(%esp)
    2b59:	00 
    2b5a:	89 44 24 08          	mov    %eax,0x8(%esp)
    2b5e:	c7 44 24 04 33 00 00 	movl   $0x33,0x4(%esp)
    2b65:	00 
    2b66:	89 14 24             	mov    %edx,(%esp)
    2b69:	e8 88 04 00 00       	call   0x2ff6
    2b6e:	66 6a 3b             	pushw  $0x3b
    2b71:	66 1f                	popw   %ds
    2b73:	c7 04 24 89 67 05 00 	movl   $0x56789,(%esp)
    2b7a:	e8 1f 02 00 00       	call   0x2d9e
    2b7f:	a1 6c 1a 00 00       	mov    0x1a6c,%eax
    2b84:	bb 0a 1a 00 00       	mov    $0x1a0a,%ebx
    2b89:	b9 00 00 01 00       	mov    $0x10000,%ecx
    2b8e:	89 c2                	mov    %eax,%edx
    2b90:	cd 24                	int    $0x24
    2b92:	8d 85 41 ff ff ff    	lea    -0xbf(%ebp),%eax
    2b98:	89 c1                	mov    %eax,%ecx
    2b9a:	e8 81 04 00 00       	call   0x3020
    2b9f:	8d 85 50 ff ff ff    	lea    -0xb0(%ebp),%eax
    2ba5:	89 c1                	mov    %eax,%ecx
    2ba7:	e8 74 04 00 00       	call   0x3020
    2bac:	8d 85 5f ff ff ff    	lea    -0xa1(%ebp),%eax
    2bb2:	89 c1                	mov    %eax,%ecx
    2bb4:	e8 67 04 00 00       	call   0x3020
    2bb9:	8d 85 6e ff ff ff    	lea    -0x92(%ebp),%eax
    2bbf:	89 c1                	mov    %eax,%ecx
    2bc1:	e8 a4 0a 00 00       	call   0x366a
    2bc6:	8d 85 79 ff ff ff    	lea    -0x87(%ebp),%eax
    2bcc:	89 c1                	mov    %eax,%ecx
    2bce:	e8 4d 04 00 00       	call   0x3020
    2bd3:	8d 45 88             	lea    -0x78(%ebp),%eax
    2bd6:	89 c1                	mov    %eax,%ecx
    2bd8:	e8 83 0c 00 00       	call   0x3860
    2bdd:	90                   	nop
    2bde:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    2be1:	c9                   	leave  
    2be2:	c3                   	ret    
    2be3:	55                   	push   %ebp
    2be4:	89 e5                	mov    %esp,%ebp
    2be6:	53                   	push   %ebx
    2be7:	83 ec 24             	sub    $0x24,%esp
    2bea:	89 d0                	mov    %edx,%eax
    2bec:	89 4d f4             	mov    %ecx,-0xc(%ebp)
    2bef:	89 5d f0             	mov    %ebx,-0x10(%ebp)
    2bf2:	89 45 ec             	mov    %eax,-0x14(%ebp)
    2bf5:	8b 45 f4             	mov    -0xc(%ebp),%eax
    2bf8:	89 04 24             	mov    %eax,(%esp)
    2bfb:	e8 6c 03 00 00       	call   0x2f6c
    2c00:	8b 45 f0             	mov    -0x10(%ebp),%eax
    2c03:	8b 55 ec             	mov    -0x14(%ebp),%edx
    2c06:	89 54 24 04          	mov    %edx,0x4(%esp)
    2c0a:	89 04 24             	mov    %eax,(%esp)
    2c0d:	e8 88 00 00 00       	call   0x2c9a
    2c12:	8b 45 f4             	mov    -0xc(%ebp),%eax
    2c15:	89 04 24             	mov    %eax,(%esp)
    2c18:	e8 65 03 00 00       	call   0x2f82
    2c1d:	c9                   	leave  
    2c1e:	cf                   	iret   
    2c1f:	90                   	nop
    2c20:	83 c4 24             	add    $0x24,%esp
    2c23:	5b                   	pop    %ebx
    2c24:	5d                   	pop    %ebp
    2c25:	c3                   	ret    
    2c26:	90                   	nop
    2c27:	90                   	nop
    2c28:	55                   	push   %ebp
    2c29:	89 e5                	mov    %esp,%ebp
    2c2b:	83 ec 28             	sub    $0x28,%esp
    2c2e:	89 4d f4             	mov    %ecx,-0xc(%ebp)
    2c31:	c7 44 24 04 07 00 00 	movl   $0x7,0x4(%esp)
    2c38:	00 
    2c39:	c7 04 24 78 1a 00 00 	movl   $0x1a78,(%esp)
    2c40:	e8 55 00 00 00       	call   0x2c9a
    2c45:	e8 0e 01 00 00       	call   0x2d58
    2c4a:	90                   	nop
    2c4b:	c9                   	leave  
    2c4c:	c3                   	ret    
    2c4d:	90                   	nop
    2c4e:	55                   	push   %ebp
    2c4f:	89 e5                	mov    %esp,%ebp
    2c51:	83 ec 28             	sub    $0x28,%esp
    2c54:	89 4d f4             	mov    %ecx,-0xc(%ebp)
    2c57:	c7 44 24 04 07 00 00 	movl   $0x7,0x4(%esp)
    2c5e:	00 
    2c5f:	c7 04 24 80 1a 00 00 	movl   $0x1a80,(%esp)
    2c66:	e8 2f 00 00 00       	call   0x2c9a
    2c6b:	e8 e8 00 00 00       	call   0x2d58
    2c70:	90                   	nop
    2c71:	c9                   	leave  
    2c72:	c3                   	ret    
    2c73:	90                   	nop
    2c74:	55                   	push   %ebp
    2c75:	89 e5                	mov    %esp,%ebp
    2c77:	83 ec 28             	sub    $0x28,%esp
    2c7a:	89 4d f4             	mov    %ecx,-0xc(%ebp)
    2c7d:	c7 44 24 04 07 00 00 	movl   $0x7,0x4(%esp)
    2c84:	00 
    2c85:	c7 04 24 8b 1a 00 00 	movl   $0x1a8b,(%esp)
    2c8c:	e8 09 00 00 00       	call   0x2c9a
    2c91:	e8 c2 00 00 00       	call   0x2d58
    2c96:	90                   	nop
    2c97:	c9                   	leave  
    2c98:	c3                   	ret    
    2c99:	90                   	nop
    2c9a:	55                   	push   %ebp
    2c9b:	89 e5                	mov    %esp,%ebp
    2c9d:	83 ec 18             	sub    $0x18,%esp
    2ca0:	8b 45 08             	mov    0x8(%ebp),%eax
    2ca3:	0f b6 00             	movzbl (%eax),%eax
    2ca6:	84 c0                	test   %al,%al
    2ca8:	74 20                	je     0x2cca
    2caa:	8b 45 08             	mov    0x8(%ebp),%eax
    2cad:	8d 50 01             	lea    0x1(%eax),%edx
    2cb0:	89 55 08             	mov    %edx,0x8(%ebp)
    2cb3:	0f b6 00             	movzbl (%eax),%eax
    2cb6:	0f be c0             	movsbl %al,%eax
    2cb9:	8b 55 0c             	mov    0xc(%ebp),%edx
    2cbc:	89 54 24 04          	mov    %edx,0x4(%esp)
    2cc0:	89 04 24             	mov    %eax,(%esp)
    2cc3:	e8 06 00 00 00       	call   0x2cce
    2cc8:	eb d6                	jmp    0x2ca0
    2cca:	90                   	nop
    2ccb:	c9                   	leave  
    2ccc:	c3                   	ret    
    2ccd:	90                   	nop
    2cce:	55                   	push   %ebp
    2ccf:	89 e5                	mov    %esp,%ebp
    2cd1:	53                   	push   %ebx
    2cd2:	83 ec 24             	sub    $0x24,%esp
    2cd5:	8b 45 08             	mov    0x8(%ebp),%eax
    2cd8:	88 45 e4             	mov    %al,-0x1c(%ebp)
    2cdb:	80 7d e4 0a          	cmpb   $0xa,-0x1c(%ebp)
    2cdf:	75 07                	jne    0x2ce8
    2ce1:	e8 72 00 00 00       	call   0x2d58
    2ce6:	eb 69                	jmp    0x2d51
    2ce8:	80 7d e4 0d          	cmpb   $0xd,-0x1c(%ebp)
    2cec:	75 0c                	jne    0x2cfa
    2cee:	c7 05 20 1a 00 00 00 	movl   $0x0,0x1a20
    2cf5:	00 00 00 
    2cf8:	eb 57                	jmp    0x2d51
    2cfa:	a1 20 1a 00 00       	mov    0x1a20,%eax
    2cff:	3d a0 00 00 00       	cmp    $0xa0,%eax
    2d04:	75 05                	jne    0x2d0b
    2d06:	e8 4d 00 00 00       	call   0x2d58
    2d0b:	8b 15 1c 1a 00 00    	mov    0x1a1c,%edx
    2d11:	89 d0                	mov    %edx,%eax
    2d13:	c1 e0 02             	shl    $0x2,%eax
    2d16:	01 d0                	add    %edx,%eax
    2d18:	c1 e0 05             	shl    $0x5,%eax
    2d1b:	89 c2                	mov    %eax,%edx
    2d1d:	a1 20 1a 00 00       	mov    0x1a20,%eax
    2d22:	01 d0                	add    %edx,%eax
    2d24:	89 45 f4             	mov    %eax,-0xc(%ebp)
    2d27:	8b 15 18 1a 00 00    	mov    0x1a18,%edx
    2d2d:	0f b6 45 e4          	movzbl -0x1c(%ebp),%eax
    2d31:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    2d34:	8b 4d 0c             	mov    0xc(%ebp),%ecx
    2d37:	06                   	push   %es
    2d38:	8e c2                	mov    %edx,%es
    2d3a:	26 67 88 07          	mov    %al,%es:(%bx)
    2d3e:	43                   	inc    %ebx
    2d3f:	26 67 88 0f          	mov    %cl,%es:(%bx)
    2d43:	07                   	pop    %es
    2d44:	a1 20 1a 00 00       	mov    0x1a20,%eax
    2d49:	83 c0 02             	add    $0x2,%eax
    2d4c:	a3 20 1a 00 00       	mov    %eax,0x1a20
    2d51:	83 c4 24             	add    $0x24,%esp
    2d54:	5b                   	pop    %ebx
    2d55:	5d                   	pop    %ebp
    2d56:	c3                   	ret    
    2d57:	90                   	nop
    2d58:	55                   	push   %ebp
    2d59:	89 e5                	mov    %esp,%ebp
    2d5b:	c7 05 20 1a 00 00 00 	movl   $0x0,0x1a20
    2d62:	00 00 00 
    2d65:	a1 1c 1a 00 00       	mov    0x1a1c,%eax
    2d6a:	8d 48 01             	lea    0x1(%eax),%ecx
    2d6d:	ba 1f 85 eb 51       	mov    $0x51eb851f,%edx
    2d72:	89 c8                	mov    %ecx,%eax
    2d74:	f7 ea                	imul   %edx
    2d76:	c1 fa 03             	sar    $0x3,%edx
    2d79:	89 c8                	mov    %ecx,%eax
    2d7b:	c1 f8 1f             	sar    $0x1f,%eax
    2d7e:	29 c2                	sub    %eax,%edx
    2d80:	89 d0                	mov    %edx,%eax
    2d82:	c1 e0 02             	shl    $0x2,%eax
    2d85:	01 d0                	add    %edx,%eax
    2d87:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
    2d8e:	01 d0                	add    %edx,%eax
    2d90:	29 c1                	sub    %eax,%ecx
    2d92:	89 ca                	mov    %ecx,%edx
    2d94:	89 15 1c 1a 00 00    	mov    %edx,0x1a1c
    2d9a:	90                   	nop
    2d9b:	5d                   	pop    %ebp
    2d9c:	c3                   	ret    
    2d9d:	90                   	nop
    2d9e:	55                   	push   %ebp
    2d9f:	89 e5                	mov    %esp,%ebp
    2da1:	90                   	nop
    2da2:	90                   	nop
    2da3:	5d                   	pop    %ebp
    2da4:	c3                   	ret    
    2da5:	90                   	nop
    2da6:	55                   	push   %ebp
    2da7:	89 e5                	mov    %esp,%ebp
    2da9:	53                   	push   %ebx
    2daa:	83 ec 10             	sub    $0x10,%esp
    2dad:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2db4:	74 06                	je     0x2dbc
    2db6:	8b 45 08             	mov    0x8(%ebp),%eax
    2db9:	1e                   	push   %ds
    2dba:	8e d8                	mov    %eax,%ds
    2dbc:	8b 55 0c             	mov    0xc(%ebp),%edx
    2dbf:	8b 45 08             	mov    0x8(%ebp),%eax
    2dc2:	89 d3                	mov    %edx,%ebx
    2dc4:	8b 03                	mov    (%ebx),%eax
    2dc6:	89 45 f8             	mov    %eax,-0x8(%ebp)
    2dc9:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2dd0:	74 01                	je     0x2dd3
    2dd2:	1f                   	pop    %ds
    2dd3:	8b 45 f8             	mov    -0x8(%ebp),%eax
    2dd6:	83 c4 10             	add    $0x10,%esp
    2dd9:	5b                   	pop    %ebx
    2dda:	5d                   	pop    %ebp
    2ddb:	c3                   	ret    
    2ddc:	55                   	push   %ebp
    2ddd:	89 e5                	mov    %esp,%ebp
    2ddf:	53                   	push   %ebx
    2de0:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2de7:	74 06                	je     0x2def
    2de9:	8b 45 08             	mov    0x8(%ebp),%eax
    2dec:	1e                   	push   %ds
    2ded:	8e d8                	mov    %eax,%ds
    2def:	8b 5d 0c             	mov    0xc(%ebp),%ebx
    2df2:	8a 45 10             	mov    0x10(%ebp),%al
    2df5:	88 03                	mov    %al,(%ebx)
    2df7:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2dfe:	74 01                	je     0x2e01
    2e00:	1f                   	pop    %ds
    2e01:	90                   	nop
    2e02:	5b                   	pop    %ebx
    2e03:	5d                   	pop    %ebp
    2e04:	c3                   	ret    
    2e05:	90                   	nop
    2e06:	55                   	push   %ebp
    2e07:	89 e5                	mov    %esp,%ebp
    2e09:	53                   	push   %ebx
    2e0a:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2e11:	74 06                	je     0x2e19
    2e13:	8b 45 08             	mov    0x8(%ebp),%eax
    2e16:	1e                   	push   %ds
    2e17:	8e d8                	mov    %eax,%ds
    2e19:	8b 5d 0c             	mov    0xc(%ebp),%ebx
    2e1c:	66 8b 45 10          	mov    0x10(%ebp),%ax
    2e20:	66 89 03             	mov    %ax,(%ebx)
    2e23:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2e2a:	74 01                	je     0x2e2d
    2e2c:	1f                   	pop    %ds
    2e2d:	90                   	nop
    2e2e:	5b                   	pop    %ebx
    2e2f:	5d                   	pop    %ebp
    2e30:	c3                   	ret    
    2e31:	90                   	nop
    2e32:	55                   	push   %ebp
    2e33:	89 e5                	mov    %esp,%ebp
    2e35:	53                   	push   %ebx
    2e36:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2e3d:	74 06                	je     0x2e45
    2e3f:	8b 45 08             	mov    0x8(%ebp),%eax
    2e42:	1e                   	push   %ds
    2e43:	8e d8                	mov    %eax,%ds
    2e45:	8b 5d 0c             	mov    0xc(%ebp),%ebx
    2e48:	8b 45 10             	mov    0x10(%ebp),%eax
    2e4b:	89 03                	mov    %eax,(%ebx)
    2e4d:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2e54:	74 01                	je     0x2e57
    2e56:	1f                   	pop    %ds
    2e57:	90                   	nop
    2e58:	5b                   	pop    %ebx
    2e59:	5d                   	pop    %ebp
    2e5a:	c3                   	ret    
    2e5b:	90                   	nop
    2e5c:	55                   	push   %ebp
    2e5d:	89 e5                	mov    %esp,%ebp
    2e5f:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2e66:	74 06                	je     0x2e6e
    2e68:	8b 45 08             	mov    0x8(%ebp),%eax
    2e6b:	1e                   	push   %ds
    2e6c:	8e d8                	mov    %eax,%ds
    2e6e:	06                   	push   %es
    2e6f:	81 7d 10 00 00 01 00 	cmpl   $0x10000,0x10(%ebp)
    2e76:	75 04                	jne    0x2e7c
    2e78:	1e                   	push   %ds
    2e79:	07                   	pop    %es
    2e7a:	eb 05                	jmp    0x2e81
    2e7c:	8b 45 10             	mov    0x10(%ebp),%eax
    2e7f:	8e c0                	mov    %eax,%es
    2e81:	56                   	push   %esi
    2e82:	57                   	push   %edi
    2e83:	8b 75 0c             	mov    0xc(%ebp),%esi
    2e86:	8b 7d 14             	mov    0x14(%ebp),%edi
    2e89:	8b 4d 18             	mov    0x18(%ebp),%ecx
    2e8c:	fc                   	cld    
    2e8d:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
    2e8f:	5f                   	pop    %edi
    2e90:	5e                   	pop    %esi
    2e91:	07                   	pop    %es
    2e92:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2e99:	74 01                	je     0x2e9c
    2e9b:	1f                   	pop    %ds
    2e9c:	90                   	nop
    2e9d:	5d                   	pop    %ebp
    2e9e:	c3                   	ret    
    2e9f:	90                   	nop
    2ea0:	55                   	push   %ebp
    2ea1:	89 e5                	mov    %esp,%ebp
    2ea3:	83 ec 28             	sub    $0x28,%esp
    2ea6:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
    2ead:	00 
    2eae:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
    2eb5:	e8 52 00 00 00       	call   0x2f0c
    2eba:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
    2ec1:	83 7d f4 19          	cmpl   $0x19,-0xc(%ebp)
    2ec5:	74 2d                	je     0x2ef4
    2ec7:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
    2ece:	83 7d f0 50          	cmpl   $0x50,-0x10(%ebp)
    2ed2:	74 1a                	je     0x2eee
    2ed4:	c7 44 24 04 07 00 00 	movl   $0x7,0x4(%esp)
    2edb:	00 
    2edc:	c7 04 24 20 00 00 00 	movl   $0x20,(%esp)
    2ee3:	e8 e6 fd ff ff       	call   0x2cce
    2ee8:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
    2eec:	eb e0                	jmp    0x2ece
    2eee:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
    2ef2:	eb cd                	jmp    0x2ec1
    2ef4:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
    2efb:	00 
    2efc:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
    2f03:	e8 04 00 00 00       	call   0x2f0c
    2f08:	90                   	nop
    2f09:	c9                   	leave  
    2f0a:	c3                   	ret    
    2f0b:	90                   	nop
    2f0c:	55                   	push   %ebp
    2f0d:	89 e5                	mov    %esp,%ebp
    2f0f:	8b 4d 08             	mov    0x8(%ebp),%ecx
    2f12:	ba 1f 85 eb 51       	mov    $0x51eb851f,%edx
    2f17:	89 c8                	mov    %ecx,%eax
    2f19:	f7 ea                	imul   %edx
    2f1b:	c1 fa 03             	sar    $0x3,%edx
    2f1e:	89 c8                	mov    %ecx,%eax
    2f20:	c1 f8 1f             	sar    $0x1f,%eax
    2f23:	29 c2                	sub    %eax,%edx
    2f25:	89 d0                	mov    %edx,%eax
    2f27:	c1 e0 02             	shl    $0x2,%eax
    2f2a:	01 d0                	add    %edx,%eax
    2f2c:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
    2f33:	01 d0                	add    %edx,%eax
    2f35:	29 c1                	sub    %eax,%ecx
    2f37:	89 ca                	mov    %ecx,%edx
    2f39:	89 15 1c 1a 00 00    	mov    %edx,0x1a1c
    2f3f:	8b 4d 0c             	mov    0xc(%ebp),%ecx
    2f42:	ba 67 66 66 66       	mov    $0x66666667,%edx
    2f47:	89 c8                	mov    %ecx,%eax
    2f49:	f7 ea                	imul   %edx
    2f4b:	c1 fa 05             	sar    $0x5,%edx
    2f4e:	89 c8                	mov    %ecx,%eax
    2f50:	c1 f8 1f             	sar    $0x1f,%eax
    2f53:	29 c2                	sub    %eax,%edx
    2f55:	89 d0                	mov    %edx,%eax
    2f57:	c1 e0 02             	shl    $0x2,%eax
    2f5a:	01 d0                	add    %edx,%eax
    2f5c:	c1 e0 04             	shl    $0x4,%eax
    2f5f:	29 c1                	sub    %eax,%ecx
    2f61:	89 ca                	mov    %ecx,%edx
    2f63:	89 15 20 1a 00 00    	mov    %edx,0x1a20
    2f69:	90                   	nop
    2f6a:	5d                   	pop    %ebp
    2f6b:	c3                   	ret    
    2f6c:	55                   	push   %ebp
    2f6d:	89 e5                	mov    %esp,%ebp
    2f6f:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2f76:	74 06                	je     0x2f7e
    2f78:	8b 45 08             	mov    0x8(%ebp),%eax
    2f7b:	1e                   	push   %ds
    2f7c:	8e d8                	mov    %eax,%ds
    2f7e:	90                   	nop
    2f7f:	5d                   	pop    %ebp
    2f80:	c3                   	ret    
    2f81:	90                   	nop
    2f82:	55                   	push   %ebp
    2f83:	89 e5                	mov    %esp,%ebp
    2f85:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2f8c:	74 01                	je     0x2f8f
    2f8e:	1f                   	pop    %ds
    2f8f:	90                   	nop
    2f90:	5d                   	pop    %ebp
    2f91:	c3                   	ret    
    2f92:	55                   	push   %ebp
    2f93:	89 e5                	mov    %esp,%ebp
    2f95:	06                   	push   %es
    2f96:	81 7d 08 00 00 01 00 	cmpl   $0x10000,0x8(%ebp)
    2f9d:	75 04                	jne    0x2fa3
    2f9f:	1e                   	push   %ds
    2fa0:	07                   	pop    %es
    2fa1:	eb 05                	jmp    0x2fa8
    2fa3:	8b 45 08             	mov    0x8(%ebp),%eax
    2fa6:	8e c0                	mov    %eax,%es
    2fa8:	90                   	nop
    2fa9:	5d                   	pop    %ebp
    2faa:	c3                   	ret    
    2fab:	90                   	nop
    2fac:	55                   	push   %ebp
    2fad:	89 e5                	mov    %esp,%ebp
    2faf:	07                   	pop    %es
    2fb0:	90                   	nop
    2fb1:	5d                   	pop    %ebp
    2fb2:	c3                   	ret    
    2fb3:	90                   	nop
    2fb4:	55                   	push   %ebp
    2fb5:	89 e5                	mov    %esp,%ebp
    2fb7:	0f 00 5d 08          	ltr    0x8(%ebp)
    2fbb:	90                   	nop
    2fbc:	5d                   	pop    %ebp
    2fbd:	c3                   	ret    
    2fbe:	55                   	push   %ebp
    2fbf:	89 e5                	mov    %esp,%ebp
    2fc1:	8b 45 08             	mov    0x8(%ebp),%eax
    2fc4:	c1 e0 03             	shl    $0x3,%eax
    2fc7:	89 c2                	mov    %eax,%edx
    2fc9:	8b 45 10             	mov    0x10(%ebp),%eax
    2fcc:	83 e0 01             	and    $0x1,%eax
    2fcf:	c1 e0 02             	shl    $0x2,%eax
    2fd2:	09 c2                	or     %eax,%edx
    2fd4:	8b 45 0c             	mov    0xc(%ebp),%eax
    2fd7:	83 e0 03             	and    $0x3,%eax
    2fda:	09 d0                	or     %edx,%eax
    2fdc:	5d                   	pop    %ebp
    2fdd:	c3                   	ret    
    2fde:	55                   	push   %ebp
    2fdf:	89 e5                	mov    %esp,%ebp
    2fe1:	66 8c c8             	mov    %cs,%ax
    2fe4:	24 03                	and    $0x3,%al
    2fe6:	90                   	nop
    2fe7:	5d                   	pop    %ebp
    2fe8:	c3                   	ret    
    2fe9:	90                   	nop
    2fea:	55                   	push   %ebp
    2feb:	89 e5                	mov    %esp,%ebp
    2fed:	66 8b 45 08          	mov    0x8(%ebp),%ax
    2ff1:	24 03                	and    $0x3,%al
    2ff3:	90                   	nop
    2ff4:	5d                   	pop    %ebp
    2ff5:	c3                   	ret    
    2ff6:	55                   	push   %ebp
    2ff7:	89 e5                	mov    %esp,%ebp
    2ff9:	83 c4 08             	add    $0x8,%esp
    2ffc:	cf                   	iret   
    2ffd:	90                   	nop
    2ffe:	5d                   	pop    %ebp
    2fff:	c3                   	ret    
    3000:	55                   	push   %ebp
    3001:	89 e5                	mov    %esp,%ebp
    3003:	9c                   	pushf  
    3004:	58                   	pop    %eax
    3005:	90                   	nop
    3006:	5d                   	pop    %ebp
    3007:	c3                   	ret    
    3008:	55                   	push   %ebp
    3009:	89 e5                	mov    %esp,%ebp
    300b:	83 ec 04             	sub    $0x4,%esp
    300e:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    3011:	90                   	nop
    3012:	c9                   	leave  
    3013:	c3                   	ret    
    3014:	55                   	push   %ebp
    3015:	89 e5                	mov    %esp,%ebp
    3017:	83 ec 04             	sub    $0x4,%esp
    301a:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    301d:	90                   	nop
    301e:	c9                   	leave  
    301f:	c3                   	ret    
    3020:	55                   	push   %ebp
    3021:	89 e5                	mov    %esp,%ebp
    3023:	83 ec 04             	sub    $0x4,%esp
    3026:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    3029:	8b 45 fc             	mov    -0x4(%ebp),%eax
    302c:	89 c1                	mov    %eax,%ecx
    302e:	e8 e1 ff ff ff       	call   0x3014
    3033:	90                   	nop
    3034:	c9                   	leave  
    3035:	c3                   	ret    
    3036:	55                   	push   %ebp
    3037:	89 e5                	mov    %esp,%ebp
    3039:	56                   	push   %esi
    303a:	53                   	push   %ebx
    303b:	83 ec 1c             	sub    $0x1c,%esp
    303e:	89 4d f4             	mov    %ecx,-0xc(%ebp)
    3041:	8b 45 10             	mov    0x10(%ebp),%eax
    3044:	8b 5d 14             	mov    0x14(%ebp),%ebx
    3047:	8b 4d 18             	mov    0x18(%ebp),%ecx
    304a:	8b 55 1c             	mov    0x1c(%ebp),%edx
    304d:	8b 75 20             	mov    0x20(%ebp),%esi
    3050:	89 75 dc             	mov    %esi,-0x24(%ebp)
    3053:	88 45 f0             	mov    %al,-0x10(%ebp)
    3056:	88 5d ec             	mov    %bl,-0x14(%ebp)
    3059:	88 4d e8             	mov    %cl,-0x18(%ebp)
    305c:	88 55 e4             	mov    %dl,-0x1c(%ebp)
    305f:	0f b6 45 dc          	movzbl -0x24(%ebp),%eax
    3063:	88 45 e0             	mov    %al,-0x20(%ebp)
    3066:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3069:	89 c1                	mov    %eax,%ecx
    306b:	e8 98 ff ff ff       	call   0x3008
    3070:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3073:	c6 40 04 00          	movb   $0x0,0x4(%eax)
    3077:	8b 45 f4             	mov    -0xc(%ebp),%eax
    307a:	0f b6 55 e4          	movzbl -0x1c(%ebp),%edx
    307e:	88 50 05             	mov    %dl,0x5(%eax)
    3081:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3084:	c6 40 06 00          	movb   $0x0,0x6(%eax)
    3088:	8b 45 f4             	mov    -0xc(%ebp),%eax
    308b:	c6 40 07 00          	movb   $0x0,0x7(%eax)
    308f:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3092:	0f b6 55 e0          	movzbl -0x20(%ebp),%edx
    3096:	88 50 0b             	mov    %dl,0xb(%eax)
    3099:	8b 45 f4             	mov    -0xc(%ebp),%eax
    309c:	0f b6 55 ec          	movzbl -0x14(%ebp),%edx
    30a0:	88 50 0c             	mov    %dl,0xc(%eax)
    30a3:	8b 45 f4             	mov    -0xc(%ebp),%eax
    30a6:	0f b6 55 e8          	movzbl -0x18(%ebp),%edx
    30aa:	88 50 0d             	mov    %dl,0xd(%eax)
    30ad:	8b 45 f4             	mov    -0xc(%ebp),%eax
    30b0:	0f b6 55 f0          	movzbl -0x10(%ebp),%edx
    30b4:	88 50 0e             	mov    %dl,0xe(%eax)
    30b7:	8b 45 f4             	mov    -0xc(%ebp),%eax
    30ba:	8b 55 08             	mov    0x8(%ebp),%edx
    30bd:	89 10                	mov    %edx,(%eax)
    30bf:	8b 45 f4             	mov    -0xc(%ebp),%eax
    30c2:	83 c0 08             	add    $0x8,%eax
    30c5:	8b 55 0c             	mov    0xc(%ebp),%edx
    30c8:	66 89 10             	mov    %dx,(%eax)
    30cb:	8b 45 0c             	mov    0xc(%ebp),%eax
    30ce:	25 00 00 0f 00       	and    $0xf0000,%eax
    30d3:	c1 f8 10             	sar    $0x10,%eax
    30d6:	89 c2                	mov    %eax,%edx
    30d8:	8b 45 f4             	mov    -0xc(%ebp),%eax
    30db:	88 50 0a             	mov    %dl,0xa(%eax)
    30de:	90                   	nop
    30df:	83 c4 1c             	add    $0x1c,%esp
    30e2:	5b                   	pop    %ebx
    30e3:	5e                   	pop    %esi
    30e4:	5d                   	pop    %ebp
    30e5:	c2 1c 00             	ret    $0x1c
    30e8:	55                   	push   %ebp
    30e9:	89 e5                	mov    %esp,%ebp
    30eb:	83 ec 04             	sub    $0x4,%esp
    30ee:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    30f1:	8b 45 fc             	mov    -0x4(%ebp),%eax
    30f4:	8b 10                	mov    (%eax),%edx
    30f6:	8b 45 08             	mov    0x8(%ebp),%eax
    30f9:	8b 00                	mov    (%eax),%eax
    30fb:	39 c2                	cmp    %eax,%edx
    30fd:	0f 85 bc 00 00 00    	jne    0x31bf
    3103:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3106:	83 c0 08             	add    $0x8,%eax
    3109:	8b 10                	mov    (%eax),%edx
    310b:	8b 45 08             	mov    0x8(%ebp),%eax
    310e:	83 c0 08             	add    $0x8,%eax
    3111:	0f b7 00             	movzwl (%eax),%eax
    3114:	98                   	cwtl   
    3115:	31 d0                	xor    %edx,%eax
    3117:	25 ff ff 0f 00       	and    $0xfffff,%eax
    311c:	85 c0                	test   %eax,%eax
    311e:	0f 85 9b 00 00 00    	jne    0x31bf
    3124:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3127:	0f b6 50 0b          	movzbl 0xb(%eax),%edx
    312b:	8b 45 08             	mov    0x8(%ebp),%eax
    312e:	0f b6 40 0b          	movzbl 0xb(%eax),%eax
    3132:	38 c2                	cmp    %al,%dl
    3134:	0f 85 85 00 00 00    	jne    0x31bf
    313a:	8b 45 fc             	mov    -0x4(%ebp),%eax
    313d:	0f b6 50 06          	movzbl 0x6(%eax),%edx
    3141:	8b 45 08             	mov    0x8(%ebp),%eax
    3144:	0f b6 40 06          	movzbl 0x6(%eax),%eax
    3148:	38 c2                	cmp    %al,%dl
    314a:	75 73                	jne    0x31bf
    314c:	8b 45 fc             	mov    -0x4(%ebp),%eax
    314f:	0f b6 50 05          	movzbl 0x5(%eax),%edx
    3153:	8b 45 08             	mov    0x8(%ebp),%eax
    3156:	0f b6 40 05          	movzbl 0x5(%eax),%eax
    315a:	38 c2                	cmp    %al,%dl
    315c:	75 61                	jne    0x31bf
    315e:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3161:	0f b6 50 0d          	movzbl 0xd(%eax),%edx
    3165:	8b 45 08             	mov    0x8(%ebp),%eax
    3168:	0f b6 40 0d          	movzbl 0xd(%eax),%eax
    316c:	38 c2                	cmp    %al,%dl
    316e:	75 4f                	jne    0x31bf
    3170:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3173:	0f b6 50 0e          	movzbl 0xe(%eax),%edx
    3177:	8b 45 08             	mov    0x8(%ebp),%eax
    317a:	0f b6 40 0e          	movzbl 0xe(%eax),%eax
    317e:	38 c2                	cmp    %al,%dl
    3180:	75 3d                	jne    0x31bf
    3182:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3185:	0f b6 50 04          	movzbl 0x4(%eax),%edx
    3189:	8b 45 08             	mov    0x8(%ebp),%eax
    318c:	0f b6 40 04          	movzbl 0x4(%eax),%eax
    3190:	38 c2                	cmp    %al,%dl
    3192:	75 2b                	jne    0x31bf
    3194:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3197:	0f b6 50 07          	movzbl 0x7(%eax),%edx
    319b:	8b 45 08             	mov    0x8(%ebp),%eax
    319e:	0f b6 40 07          	movzbl 0x7(%eax),%eax
    31a2:	38 c2                	cmp    %al,%dl
    31a4:	75 19                	jne    0x31bf
    31a6:	8b 45 fc             	mov    -0x4(%ebp),%eax
    31a9:	0f b6 50 0c          	movzbl 0xc(%eax),%edx
    31ad:	8b 45 08             	mov    0x8(%ebp),%eax
    31b0:	0f b6 40 0c          	movzbl 0xc(%eax),%eax
    31b4:	38 c2                	cmp    %al,%dl
    31b6:	75 07                	jne    0x31bf
    31b8:	b8 01 00 00 00       	mov    $0x1,%eax
    31bd:	eb 05                	jmp    0x31c4
    31bf:	b8 00 00 00 00       	mov    $0x0,%eax
    31c4:	c9                   	leave  
    31c5:	c2 04 00             	ret    $0x4
    31c8:	55                   	push   %ebp
    31c9:	89 e5                	mov    %esp,%ebp
    31cb:	83 ec 38             	sub    $0x38,%esp
    31ce:	89 4d e4             	mov    %ecx,-0x1c(%ebp)
    31d1:	8b 45 0c             	mov    0xc(%ebp),%eax
    31d4:	89 45 f4             	mov    %eax,-0xc(%ebp)
    31d7:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    31da:	83 c0 08             	add    $0x8,%eax
    31dd:	0f b7 00             	movzwl (%eax),%eax
    31e0:	98                   	cwtl   
    31e1:	0f b7 d0             	movzwl %ax,%edx
    31e4:	8b 45 f4             	mov    -0xc(%ebp),%eax
    31e7:	89 54 24 08          	mov    %edx,0x8(%esp)
    31eb:	89 44 24 04          	mov    %eax,0x4(%esp)
    31ef:	8b 45 08             	mov    0x8(%ebp),%eax
    31f2:	89 04 24             	mov    %eax,(%esp)
    31f5:	e8 0c fc ff ff       	call   0x2e06
    31fa:	83 45 f4 02          	addl   $0x2,-0xc(%ebp)
    31fe:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    3201:	8b 00                	mov    (%eax),%eax
    3203:	0f b7 d0             	movzwl %ax,%edx
    3206:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3209:	89 54 24 08          	mov    %edx,0x8(%esp)
    320d:	89 44 24 04          	mov    %eax,0x4(%esp)
    3211:	8b 45 08             	mov    0x8(%ebp),%eax
    3214:	89 04 24             	mov    %eax,(%esp)
    3217:	e8 ea fb ff ff       	call   0x2e06
    321c:	83 45 f4 02          	addl   $0x2,-0xc(%ebp)
    3220:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    3223:	8b 00                	mov    (%eax),%eax
    3225:	25 00 00 ff 00       	and    $0xff0000,%eax
    322a:	c1 f8 10             	sar    $0x10,%eax
    322d:	89 c2                	mov    %eax,%edx
    322f:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3232:	89 54 24 08          	mov    %edx,0x8(%esp)
    3236:	89 44 24 04          	mov    %eax,0x4(%esp)
    323a:	8b 45 08             	mov    0x8(%ebp),%eax
    323d:	89 04 24             	mov    %eax,(%esp)
    3240:	e8 97 fb ff ff       	call   0x2ddc
    3245:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
    3249:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    324c:	0f b6 40 0b          	movzbl 0xb(%eax),%eax
    3250:	0f be c0             	movsbl %al,%eax
    3253:	c1 e0 07             	shl    $0x7,%eax
    3256:	0f b6 d0             	movzbl %al,%edx
    3259:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    325c:	0f b6 40 0c          	movzbl 0xc(%eax),%eax
    3260:	0f be c0             	movsbl %al,%eax
    3263:	83 e0 03             	and    $0x3,%eax
    3266:	c1 e0 05             	shl    $0x5,%eax
    3269:	09 c2                	or     %eax,%edx
    326b:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    326e:	0f b6 40 0d          	movzbl 0xd(%eax),%eax
    3272:	0f be c0             	movsbl %al,%eax
    3275:	83 e0 01             	and    $0x1,%eax
    3278:	c1 e0 04             	shl    $0x4,%eax
    327b:	09 c2                	or     %eax,%edx
    327d:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    3280:	0f b6 40 0e          	movzbl 0xe(%eax),%eax
    3284:	0f be c0             	movsbl %al,%eax
    3287:	83 e0 0f             	and    $0xf,%eax
    328a:	09 c2                	or     %eax,%edx
    328c:	8b 45 f4             	mov    -0xc(%ebp),%eax
    328f:	89 54 24 08          	mov    %edx,0x8(%esp)
    3293:	89 44 24 04          	mov    %eax,0x4(%esp)
    3297:	8b 45 08             	mov    0x8(%ebp),%eax
    329a:	89 04 24             	mov    %eax,(%esp)
    329d:	e8 3a fb ff ff       	call   0x2ddc
    32a2:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
    32a6:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    32a9:	0f b6 40 04          	movzbl 0x4(%eax),%eax
    32ad:	0f be c0             	movsbl %al,%eax
    32b0:	c1 e0 07             	shl    $0x7,%eax
    32b3:	0f b6 d0             	movzbl %al,%edx
    32b6:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    32b9:	0f b6 40 05          	movzbl 0x5(%eax),%eax
    32bd:	0f be c0             	movsbl %al,%eax
    32c0:	83 e0 01             	and    $0x1,%eax
    32c3:	c1 e0 06             	shl    $0x6,%eax
    32c6:	09 c2                	or     %eax,%edx
    32c8:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    32cb:	0f b6 40 06          	movzbl 0x6(%eax),%eax
    32cf:	0f be c0             	movsbl %al,%eax
    32d2:	83 e0 01             	and    $0x1,%eax
    32d5:	c1 e0 05             	shl    $0x5,%eax
    32d8:	09 c2                	or     %eax,%edx
    32da:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    32dd:	0f b6 40 07          	movzbl 0x7(%eax),%eax
    32e1:	0f be c0             	movsbl %al,%eax
    32e4:	83 e0 01             	and    $0x1,%eax
    32e7:	c1 e0 04             	shl    $0x4,%eax
    32ea:	09 c2                	or     %eax,%edx
    32ec:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    32ef:	83 c0 08             	add    $0x8,%eax
    32f2:	8b 00                	mov    (%eax),%eax
    32f4:	25 00 00 0f 00       	and    $0xf0000,%eax
    32f9:	c1 f8 10             	sar    $0x10,%eax
    32fc:	09 c2                	or     %eax,%edx
    32fe:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3301:	89 54 24 08          	mov    %edx,0x8(%esp)
    3305:	89 44 24 04          	mov    %eax,0x4(%esp)
    3309:	8b 45 08             	mov    0x8(%ebp),%eax
    330c:	89 04 24             	mov    %eax,(%esp)
    330f:	e8 c8 fa ff ff       	call   0x2ddc
    3314:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
    3318:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    331b:	8b 00                	mov    (%eax),%eax
    331d:	c1 e8 18             	shr    $0x18,%eax
    3320:	89 c2                	mov    %eax,%edx
    3322:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3325:	89 54 24 08          	mov    %edx,0x8(%esp)
    3329:	89 44 24 04          	mov    %eax,0x4(%esp)
    332d:	8b 45 08             	mov    0x8(%ebp),%eax
    3330:	89 04 24             	mov    %eax,(%esp)
    3333:	e8 a4 fa ff ff       	call   0x2ddc
    3338:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
    333c:	90                   	nop
    333d:	c9                   	leave  
    333e:	c2 08 00             	ret    $0x8
    3341:	90                   	nop
    3342:	55                   	push   %ebp
    3343:	89 e5                	mov    %esp,%ebp
    3345:	83 ec 28             	sub    $0x28,%esp
    3348:	8b 45 08             	mov    0x8(%ebp),%eax
    334b:	83 c0 08             	add    $0x8,%eax
    334e:	89 45 f4             	mov    %eax,-0xc(%ebp)
    3351:	8b 45 10             	mov    0x10(%ebp),%eax
    3354:	89 45 f0             	mov    %eax,-0x10(%ebp)
    3357:	8b 45 f0             	mov    -0x10(%ebp),%eax
    335a:	89 44 24 04          	mov    %eax,0x4(%esp)
    335e:	8b 45 0c             	mov    0xc(%ebp),%eax
    3361:	89 04 24             	mov    %eax,(%esp)
    3364:	e8 3d fa ff ff       	call   0x2da6
    3369:	89 c2                	mov    %eax,%edx
    336b:	8b 45 f4             	mov    -0xc(%ebp),%eax
    336e:	66 89 10             	mov    %dx,(%eax)
    3371:	83 45 f0 02          	addl   $0x2,-0x10(%ebp)
    3375:	8b 45 08             	mov    0x8(%ebp),%eax
    3378:	89 45 f4             	mov    %eax,-0xc(%ebp)
    337b:	8b 45 f0             	mov    -0x10(%ebp),%eax
    337e:	89 44 24 04          	mov    %eax,0x4(%esp)
    3382:	8b 45 0c             	mov    0xc(%ebp),%eax
    3385:	89 04 24             	mov    %eax,(%esp)
    3388:	e8 19 fa ff ff       	call   0x2da6
    338d:	89 c2                	mov    %eax,%edx
    338f:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3392:	66 89 10             	mov    %dx,(%eax)
    3395:	83 45 f0 02          	addl   $0x2,-0x10(%ebp)
    3399:	8b 45 08             	mov    0x8(%ebp),%eax
    339c:	83 c0 02             	add    $0x2,%eax
    339f:	89 45 f4             	mov    %eax,-0xc(%ebp)
    33a2:	8b 45 f0             	mov    -0x10(%ebp),%eax
    33a5:	89 44 24 04          	mov    %eax,0x4(%esp)
    33a9:	8b 45 0c             	mov    0xc(%ebp),%eax
    33ac:	89 04 24             	mov    %eax,(%esp)
    33af:	e8 f2 f9 ff ff       	call   0x2da6
    33b4:	89 c2                	mov    %eax,%edx
    33b6:	8b 45 f4             	mov    -0xc(%ebp),%eax
    33b9:	88 10                	mov    %dl,(%eax)
    33bb:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
    33bf:	8b 45 08             	mov    0x8(%ebp),%eax
    33c2:	0f b6 40 0e          	movzbl 0xe(%eax),%eax
    33c6:	0f be c0             	movsbl %al,%eax
    33c9:	89 45 f4             	mov    %eax,-0xc(%ebp)
    33cc:	8b 45 f0             	mov    -0x10(%ebp),%eax
    33cf:	89 44 24 04          	mov    %eax,0x4(%esp)
    33d3:	8b 45 0c             	mov    0xc(%ebp),%eax
    33d6:	89 04 24             	mov    %eax,(%esp)
    33d9:	e8 c8 f9 ff ff       	call   0x2da6
    33de:	83 e0 0f             	and    $0xf,%eax
    33e1:	89 c2                	mov    %eax,%edx
    33e3:	8b 45 f4             	mov    -0xc(%ebp),%eax
    33e6:	88 10                	mov    %dl,(%eax)
    33e8:	8b 45 08             	mov    0x8(%ebp),%eax
    33eb:	0f b6 40 0d          	movzbl 0xd(%eax),%eax
    33ef:	0f be c0             	movsbl %al,%eax
    33f2:	89 45 f4             	mov    %eax,-0xc(%ebp)
    33f5:	8b 45 f0             	mov    -0x10(%ebp),%eax
    33f8:	89 44 24 04          	mov    %eax,0x4(%esp)
    33fc:	8b 45 0c             	mov    0xc(%ebp),%eax
    33ff:	89 04 24             	mov    %eax,(%esp)
    3402:	e8 9f f9 ff ff       	call   0x2da6
    3407:	83 e0 10             	and    $0x10,%eax
    340a:	c1 f8 04             	sar    $0x4,%eax
    340d:	89 c2                	mov    %eax,%edx
    340f:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3412:	88 10                	mov    %dl,(%eax)
    3414:	8b 45 08             	mov    0x8(%ebp),%eax
    3417:	0f b6 40 0c          	movzbl 0xc(%eax),%eax
    341b:	0f be c0             	movsbl %al,%eax
    341e:	89 45 f4             	mov    %eax,-0xc(%ebp)
    3421:	8b 45 f0             	mov    -0x10(%ebp),%eax
    3424:	89 44 24 04          	mov    %eax,0x4(%esp)
    3428:	8b 45 0c             	mov    0xc(%ebp),%eax
    342b:	89 04 24             	mov    %eax,(%esp)
    342e:	e8 73 f9 ff ff       	call   0x2da6
    3433:	83 e0 60             	and    $0x60,%eax
    3436:	c1 f8 05             	sar    $0x5,%eax
    3439:	89 c2                	mov    %eax,%edx
    343b:	8b 45 f4             	mov    -0xc(%ebp),%eax
    343e:	88 10                	mov    %dl,(%eax)
    3440:	8b 45 08             	mov    0x8(%ebp),%eax
    3443:	0f b6 40 0b          	movzbl 0xb(%eax),%eax
    3447:	0f be c0             	movsbl %al,%eax
    344a:	89 45 f4             	mov    %eax,-0xc(%ebp)
    344d:	8b 45 f0             	mov    -0x10(%ebp),%eax
    3450:	89 44 24 04          	mov    %eax,0x4(%esp)
    3454:	8b 45 0c             	mov    0xc(%ebp),%eax
    3457:	89 04 24             	mov    %eax,(%esp)
    345a:	e8 47 f9 ff ff       	call   0x2da6
    345f:	25 80 00 00 00       	and    $0x80,%eax
    3464:	c1 f8 07             	sar    $0x7,%eax
    3467:	89 c2                	mov    %eax,%edx
    3469:	8b 45 f4             	mov    -0xc(%ebp),%eax
    346c:	88 10                	mov    %dl,(%eax)
    346e:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
    3472:	8b 45 08             	mov    0x8(%ebp),%eax
    3475:	83 c0 08             	add    $0x8,%eax
    3478:	83 c0 02             	add    $0x2,%eax
    347b:	89 45 f4             	mov    %eax,-0xc(%ebp)
    347e:	8b 45 f0             	mov    -0x10(%ebp),%eax
    3481:	89 44 24 04          	mov    %eax,0x4(%esp)
    3485:	8b 45 0c             	mov    0xc(%ebp),%eax
    3488:	89 04 24             	mov    %eax,(%esp)
    348b:	e8 16 f9 ff ff       	call   0x2da6
    3490:	83 e0 0f             	and    $0xf,%eax
    3493:	89 c2                	mov    %eax,%edx
    3495:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3498:	88 10                	mov    %dl,(%eax)
    349a:	8b 45 08             	mov    0x8(%ebp),%eax
    349d:	0f b6 40 07          	movzbl 0x7(%eax),%eax
    34a1:	0f be c0             	movsbl %al,%eax
    34a4:	89 45 f4             	mov    %eax,-0xc(%ebp)
    34a7:	8b 45 f0             	mov    -0x10(%ebp),%eax
    34aa:	89 44 24 04          	mov    %eax,0x4(%esp)
    34ae:	8b 45 0c             	mov    0xc(%ebp),%eax
    34b1:	89 04 24             	mov    %eax,(%esp)
    34b4:	e8 ed f8 ff ff       	call   0x2da6
    34b9:	83 e0 10             	and    $0x10,%eax
    34bc:	c1 f8 04             	sar    $0x4,%eax
    34bf:	89 c2                	mov    %eax,%edx
    34c1:	8b 45 f4             	mov    -0xc(%ebp),%eax
    34c4:	88 10                	mov    %dl,(%eax)
    34c6:	8b 45 08             	mov    0x8(%ebp),%eax
    34c9:	0f b6 40 06          	movzbl 0x6(%eax),%eax
    34cd:	0f be c0             	movsbl %al,%eax
    34d0:	89 45 f4             	mov    %eax,-0xc(%ebp)
    34d3:	8b 45 f0             	mov    -0x10(%ebp),%eax
    34d6:	89 44 24 04          	mov    %eax,0x4(%esp)
    34da:	8b 45 0c             	mov    0xc(%ebp),%eax
    34dd:	89 04 24             	mov    %eax,(%esp)
    34e0:	e8 c1 f8 ff ff       	call   0x2da6
    34e5:	83 e0 20             	and    $0x20,%eax
    34e8:	c1 f8 05             	sar    $0x5,%eax
    34eb:	89 c2                	mov    %eax,%edx
    34ed:	8b 45 f4             	mov    -0xc(%ebp),%eax
    34f0:	88 10                	mov    %dl,(%eax)
    34f2:	8b 45 08             	mov    0x8(%ebp),%eax
    34f5:	0f b6 40 05          	movzbl 0x5(%eax),%eax
    34f9:	0f be c0             	movsbl %al,%eax
    34fc:	89 45 f4             	mov    %eax,-0xc(%ebp)
    34ff:	8b 45 f0             	mov    -0x10(%ebp),%eax
    3502:	89 44 24 04          	mov    %eax,0x4(%esp)
    3506:	8b 45 0c             	mov    0xc(%ebp),%eax
    3509:	89 04 24             	mov    %eax,(%esp)
    350c:	e8 95 f8 ff ff       	call   0x2da6
    3511:	83 e0 40             	and    $0x40,%eax
    3514:	c1 f8 06             	sar    $0x6,%eax
    3517:	89 c2                	mov    %eax,%edx
    3519:	8b 45 f4             	mov    -0xc(%ebp),%eax
    351c:	88 10                	mov    %dl,(%eax)
    351e:	8b 45 08             	mov    0x8(%ebp),%eax
    3521:	0f b6 40 04          	movzbl 0x4(%eax),%eax
    3525:	0f be c0             	movsbl %al,%eax
    3528:	89 45 f4             	mov    %eax,-0xc(%ebp)
    352b:	8b 45 f0             	mov    -0x10(%ebp),%eax
    352e:	89 44 24 04          	mov    %eax,0x4(%esp)
    3532:	8b 45 0c             	mov    0xc(%ebp),%eax
    3535:	89 04 24             	mov    %eax,(%esp)
    3538:	e8 69 f8 ff ff       	call   0x2da6
    353d:	25 80 00 00 00       	and    $0x80,%eax
    3542:	c1 f8 07             	sar    $0x7,%eax
    3545:	89 c2                	mov    %eax,%edx
    3547:	8b 45 f4             	mov    -0xc(%ebp),%eax
    354a:	88 10                	mov    %dl,(%eax)
    354c:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
    3550:	8b 45 08             	mov    0x8(%ebp),%eax
    3553:	83 c0 03             	add    $0x3,%eax
    3556:	89 45 f4             	mov    %eax,-0xc(%ebp)
    3559:	8b 45 f0             	mov    -0x10(%ebp),%eax
    355c:	89 44 24 04          	mov    %eax,0x4(%esp)
    3560:	8b 45 0c             	mov    0xc(%ebp),%eax
    3563:	89 04 24             	mov    %eax,(%esp)
    3566:	e8 3b f8 ff ff       	call   0x2da6
    356b:	89 c2                	mov    %eax,%edx
    356d:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3570:	88 10                	mov    %dl,(%eax)
    3572:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
    3576:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
    357a:	90                   	nop
    357b:	c9                   	leave  
    357c:	c3                   	ret    
    357d:	90                   	nop
    357e:	55                   	push   %ebp
    357f:	89 e5                	mov    %esp,%ebp
    3581:	53                   	push   %ebx
    3582:	83 ec 34             	sub    $0x34,%esp
    3585:	89 4d f8             	mov    %ecx,-0x8(%ebp)
    3588:	8b 55 10             	mov    0x10(%ebp),%edx
    358b:	8b 45 14             	mov    0x14(%ebp),%eax
    358e:	89 45 d4             	mov    %eax,-0x2c(%ebp)
    3591:	8b 5d 18             	mov    0x18(%ebp),%ebx
    3594:	89 5d d0             	mov    %ebx,-0x30(%ebp)
    3597:	8b 4d 1c             	mov    0x1c(%ebp),%ecx
    359a:	89 4d cc             	mov    %ecx,-0x34(%ebp)
    359d:	8b 45 20             	mov    0x20(%ebp),%eax
    35a0:	89 45 c8             	mov    %eax,-0x38(%ebp)
    35a3:	8b 5d 24             	mov    0x24(%ebp),%ebx
    35a6:	8b 4d 28             	mov    0x28(%ebp),%ecx
    35a9:	8b 45 2c             	mov    0x2c(%ebp),%eax
    35ac:	88 55 f4             	mov    %dl,-0xc(%ebp)
    35af:	0f b6 55 d4          	movzbl -0x2c(%ebp),%edx
    35b3:	88 55 f0             	mov    %dl,-0x10(%ebp)
    35b6:	0f b6 55 d0          	movzbl -0x30(%ebp),%edx
    35ba:	88 55 ec             	mov    %dl,-0x14(%ebp)
    35bd:	0f b6 55 cc          	movzbl -0x34(%ebp),%edx
    35c1:	88 55 e8             	mov    %dl,-0x18(%ebp)
    35c4:	0f b6 55 c8          	movzbl -0x38(%ebp),%edx
    35c8:	88 55 e4             	mov    %dl,-0x1c(%ebp)
    35cb:	88 5d e0             	mov    %bl,-0x20(%ebp)
    35ce:	88 4d dc             	mov    %cl,-0x24(%ebp)
    35d1:	88 45 d8             	mov    %al,-0x28(%ebp)
    35d4:	8b 45 f8             	mov    -0x8(%ebp),%eax
    35d7:	8b 55 08             	mov    0x8(%ebp),%edx
    35da:	89 10                	mov    %edx,(%eax)
    35dc:	8b 45 f8             	mov    -0x8(%ebp),%eax
    35df:	83 c0 08             	add    $0x8,%eax
    35e2:	8b 55 0c             	mov    0xc(%ebp),%edx
    35e5:	66 89 10             	mov    %dx,(%eax)
    35e8:	8b 45 0c             	mov    0xc(%ebp),%eax
    35eb:	25 00 00 0f 00       	and    $0xf0000,%eax
    35f0:	c1 f8 10             	sar    $0x10,%eax
    35f3:	89 c2                	mov    %eax,%edx
    35f5:	8b 45 f8             	mov    -0x8(%ebp),%eax
    35f8:	88 50 0a             	mov    %dl,0xa(%eax)
    35fb:	8b 45 f8             	mov    -0x8(%ebp),%eax
    35fe:	0f b6 55 f4          	movzbl -0xc(%ebp),%edx
    3602:	88 50 0e             	mov    %dl,0xe(%eax)
    3605:	8b 45 f8             	mov    -0x8(%ebp),%eax
    3608:	0f b6 55 f0          	movzbl -0x10(%ebp),%edx
    360c:	88 50 0c             	mov    %dl,0xc(%eax)
    360f:	8b 45 f8             	mov    -0x8(%ebp),%eax
    3612:	0f b6 55 ec          	movzbl -0x14(%ebp),%edx
    3616:	88 50 0d             	mov    %dl,0xd(%eax)
    3619:	8b 45 f8             	mov    -0x8(%ebp),%eax
    361c:	0f b6 55 e8          	movzbl -0x18(%ebp),%edx
    3620:	88 50 05             	mov    %dl,0x5(%eax)
    3623:	8b 45 f8             	mov    -0x8(%ebp),%eax
    3626:	0f b6 55 e4          	movzbl -0x1c(%ebp),%edx
    362a:	88 50 0b             	mov    %dl,0xb(%eax)
    362d:	8b 45 f8             	mov    -0x8(%ebp),%eax
    3630:	0f b6 55 e0          	movzbl -0x20(%ebp),%edx
    3634:	88 50 04             	mov    %dl,0x4(%eax)
    3637:	8b 45 f8             	mov    -0x8(%ebp),%eax
    363a:	0f b6 55 dc          	movzbl -0x24(%ebp),%edx
    363e:	88 50 06             	mov    %dl,0x6(%eax)
    3641:	8b 45 f8             	mov    -0x8(%ebp),%eax
    3644:	0f b6 55 d8          	movzbl -0x28(%ebp),%edx
    3648:	88 50 07             	mov    %dl,0x7(%eax)
    364b:	90                   	nop
    364c:	83 c4 34             	add    $0x34,%esp
    364f:	5b                   	pop    %ebx
    3650:	5d                   	pop    %ebp
    3651:	c2 28 00             	ret    $0x28
    3654:	55                   	push   %ebp
    3655:	89 e5                	mov    %esp,%ebp
    3657:	83 ec 04             	sub    $0x4,%esp
    365a:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    365d:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3660:	89 c1                	mov    %eax,%ecx
    3662:	e8 a1 f9 ff ff       	call   0x3008
    3667:	90                   	nop
    3668:	c9                   	leave  
    3669:	c3                   	ret    
    366a:	55                   	push   %ebp
    366b:	89 e5                	mov    %esp,%ebp
    366d:	83 ec 04             	sub    $0x4,%esp
    3670:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    3673:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3676:	89 c1                	mov    %eax,%ecx
    3678:	e8 97 f9 ff ff       	call   0x3014
    367d:	90                   	nop
    367e:	c9                   	leave  
    367f:	c3                   	ret    
    3680:	55                   	push   %ebp
    3681:	89 e5                	mov    %esp,%ebp
    3683:	83 ec 04             	sub    $0x4,%esp
    3686:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    3689:	8b 45 fc             	mov    -0x4(%ebp),%eax
    368c:	0f b6 50 05          	movzbl 0x5(%eax),%edx
    3690:	8b 45 08             	mov    0x8(%ebp),%eax
    3693:	83 e0 11             	and    $0x11,%eax
    3696:	c1 e0 05             	shl    $0x5,%eax
    3699:	09 c2                	or     %eax,%edx
    369b:	8b 45 fc             	mov    -0x4(%ebp),%eax
    369e:	88 50 05             	mov    %dl,0x5(%eax)
    36a1:	90                   	nop
    36a2:	c9                   	leave  
    36a3:	c2 04 00             	ret    $0x4
    36a6:	55                   	push   %ebp
    36a7:	89 e5                	mov    %esp,%ebp
    36a9:	83 ec 04             	sub    $0x4,%esp
    36ac:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    36af:	8b 45 fc             	mov    -0x4(%ebp),%eax
    36b2:	0f b6 50 05          	movzbl 0x5(%eax),%edx
    36b6:	8b 45 08             	mov    0x8(%ebp),%eax
    36b9:	c1 e0 07             	shl    $0x7,%eax
    36bc:	09 c2                	or     %eax,%edx
    36be:	8b 45 fc             	mov    -0x4(%ebp),%eax
    36c1:	88 50 05             	mov    %dl,0x5(%eax)
    36c4:	90                   	nop
    36c5:	c9                   	leave  
    36c6:	c2 04 00             	ret    $0x4
    36c9:	90                   	nop
    36ca:	55                   	push   %ebp
    36cb:	89 e5                	mov    %esp,%ebp
    36cd:	83 ec 04             	sub    $0x4,%esp
    36d0:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    36d3:	8b 45 fc             	mov    -0x4(%ebp),%eax
    36d6:	0f b6 50 05          	movzbl 0x5(%eax),%edx
    36da:	8b 45 08             	mov    0x8(%ebp),%eax
    36dd:	83 e0 01             	and    $0x1,%eax
    36e0:	c1 e0 03             	shl    $0x3,%eax
    36e3:	09 c2                	or     %eax,%edx
    36e5:	8b 45 fc             	mov    -0x4(%ebp),%eax
    36e8:	88 50 05             	mov    %dl,0x5(%eax)
    36eb:	90                   	nop
    36ec:	c9                   	leave  
    36ed:	c2 04 00             	ret    $0x4
    36f0:	55                   	push   %ebp
    36f1:	89 e5                	mov    %esp,%ebp
    36f3:	83 ec 04             	sub    $0x4,%esp
    36f6:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    36f9:	8b 45 fc             	mov    -0x4(%ebp),%eax
    36fc:	8b 55 08             	mov    0x8(%ebp),%edx
    36ff:	66 89 10             	mov    %dx,(%eax)
    3702:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3705:	83 c0 06             	add    $0x6,%eax
    3708:	8b 55 08             	mov    0x8(%ebp),%edx
    370b:	c1 fa 10             	sar    $0x10,%edx
    370e:	66 89 10             	mov    %dx,(%eax)
    3711:	90                   	nop
    3712:	c9                   	leave  
    3713:	c2 04 00             	ret    $0x4
    3716:	55                   	push   %ebp
    3717:	89 e5                	mov    %esp,%ebp
    3719:	83 ec 04             	sub    $0x4,%esp
    371c:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    371f:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3722:	83 c0 02             	add    $0x2,%eax
    3725:	8b 55 08             	mov    0x8(%ebp),%edx
    3728:	66 89 10             	mov    %dx,(%eax)
    372b:	90                   	nop
    372c:	c9                   	leave  
    372d:	c2 04 00             	ret    $0x4
    3730:	55                   	push   %ebp
    3731:	89 e5                	mov    %esp,%ebp
    3733:	83 ec 04             	sub    $0x4,%esp
    3736:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    3739:	8b 45 fc             	mov    -0x4(%ebp),%eax
    373c:	83 c0 04             	add    $0x4,%eax
    373f:	8b 55 08             	mov    0x8(%ebp),%edx
    3742:	66 89 10             	mov    %dx,(%eax)
    3745:	90                   	nop
    3746:	c9                   	leave  
    3747:	c2 04 00             	ret    $0x4
    374a:	55                   	push   %ebp
    374b:	89 e5                	mov    %esp,%ebp
    374d:	83 ec 08             	sub    $0x8,%esp
    3750:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    3753:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3756:	8b 55 0c             	mov    0xc(%ebp),%edx
    3759:	89 14 24             	mov    %edx,(%esp)
    375c:	89 c1                	mov    %eax,%ecx
    375e:	e8 8d ff ff ff       	call   0x36f0
    3763:	83 ec 04             	sub    $0x4,%esp
    3766:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3769:	8b 55 08             	mov    0x8(%ebp),%edx
    376c:	89 14 24             	mov    %edx,(%esp)
    376f:	89 c1                	mov    %eax,%ecx
    3771:	e8 a0 ff ff ff       	call   0x3716
    3776:	83 ec 04             	sub    $0x4,%esp
    3779:	8b 45 fc             	mov    -0x4(%ebp),%eax
    377c:	8b 55 10             	mov    0x10(%ebp),%edx
    377f:	89 14 24             	mov    %edx,(%esp)
    3782:	89 c1                	mov    %eax,%ecx
    3784:	e8 a7 ff ff ff       	call   0x3730
    3789:	83 ec 04             	sub    $0x4,%esp
    378c:	8b 45 fc             	mov    -0x4(%ebp),%eax
    378f:	8b 55 1c             	mov    0x1c(%ebp),%edx
    3792:	89 14 24             	mov    %edx,(%esp)
    3795:	89 c1                	mov    %eax,%ecx
    3797:	e8 2e ff ff ff       	call   0x36ca
    379c:	83 ec 04             	sub    $0x4,%esp
    379f:	8b 45 fc             	mov    -0x4(%ebp),%eax
    37a2:	8b 55 14             	mov    0x14(%ebp),%edx
    37a5:	89 14 24             	mov    %edx,(%esp)
    37a8:	89 c1                	mov    %eax,%ecx
    37aa:	e8 d1 fe ff ff       	call   0x3680
    37af:	83 ec 04             	sub    $0x4,%esp
    37b2:	8b 45 fc             	mov    -0x4(%ebp),%eax
    37b5:	8b 55 18             	mov    0x18(%ebp),%edx
    37b8:	89 14 24             	mov    %edx,(%esp)
    37bb:	89 c1                	mov    %eax,%ecx
    37bd:	e8 e4 fe ff ff       	call   0x36a6
    37c2:	83 ec 04             	sub    $0x4,%esp
    37c5:	90                   	nop
    37c6:	c9                   	leave  
    37c7:	c2 18 00             	ret    $0x18
    37ca:	55                   	push   %ebp
    37cb:	89 e5                	mov    %esp,%ebp
    37cd:	83 ec 38             	sub    $0x38,%esp
    37d0:	89 4d f4             	mov    %ecx,-0xc(%ebp)
    37d3:	8b 45 f4             	mov    -0xc(%ebp),%eax
    37d6:	89 c2                	mov    %eax,%edx
    37d8:	c7 44 24 10 08 00 00 	movl   $0x8,0x10(%esp)
    37df:	00 
    37e0:	8b 45 0c             	mov    0xc(%ebp),%eax
    37e3:	89 44 24 0c          	mov    %eax,0xc(%esp)
    37e7:	8b 45 08             	mov    0x8(%ebp),%eax
    37ea:	89 44 24 08          	mov    %eax,0x8(%esp)
    37ee:	89 54 24 04          	mov    %edx,0x4(%esp)
    37f2:	c7 04 24 00 00 01 00 	movl   $0x10000,(%esp)
    37f9:	e8 5e f6 ff ff       	call   0x2e5c
    37fe:	90                   	nop
    37ff:	c9                   	leave  
    3800:	c2 08 00             	ret    $0x8
    3803:	90                   	nop
    3804:	55                   	push   %ebp
    3805:	89 e5                	mov    %esp,%ebp
    3807:	83 ec 28             	sub    $0x28,%esp
    380a:	8b 45 08             	mov    0x8(%ebp),%eax
    380d:	c7 44 24 10 08 00 00 	movl   $0x8,0x10(%esp)
    3814:	00 
    3815:	89 44 24 0c          	mov    %eax,0xc(%esp)
    3819:	c7 44 24 08 00 00 01 	movl   $0x10000,0x8(%esp)
    3820:	00 
    3821:	8b 45 10             	mov    0x10(%ebp),%eax
    3824:	89 44 24 04          	mov    %eax,0x4(%esp)
    3828:	8b 45 0c             	mov    0xc(%ebp),%eax
    382b:	89 04 24             	mov    %eax,(%esp)
    382e:	e8 29 f6 ff ff       	call   0x2e5c
    3833:	90                   	nop
    3834:	c9                   	leave  
    3835:	c3                   	ret    
    3836:	90                   	nop
    3837:	90                   	nop
    3838:	55                   	push   %ebp
    3839:	89 e5                	mov    %esp,%ebp
    383b:	83 ec 04             	sub    $0x4,%esp
    383e:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    3841:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3844:	83 c0 64             	add    $0x64,%eax
    3847:	8d 50 08             	lea    0x8(%eax),%edx
    384a:	8b 45 fc             	mov    -0x4(%ebp),%eax
    384d:	89 50 68             	mov    %edx,0x68(%eax)
    3850:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3853:	8d 50 64             	lea    0x64(%eax),%edx
    3856:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3859:	89 50 6c             	mov    %edx,0x6c(%eax)
    385c:	90                   	nop
    385d:	c9                   	leave  
    385e:	c3                   	ret    
    385f:	90                   	nop
    3860:	55                   	push   %ebp
    3861:	89 e5                	mov    %esp,%ebp
    3863:	83 ec 04             	sub    $0x4,%esp
    3866:	89 4d fc             	mov    %ecx,-0x4(%ebp)
    3869:	90                   	nop
    386a:	c9                   	leave  
    386b:	c3                   	ret    
    386c:	55                   	push   %ebp
    386d:	89 e5                	mov    %esp,%ebp
    386f:	83 ec 38             	sub    $0x38,%esp
    3872:	89 4d f4             	mov    %ecx,-0xc(%ebp)
    3875:	8b 45 f4             	mov    -0xc(%ebp),%eax
    3878:	89 c2                	mov    %eax,%edx
    387a:	c7 44 24 10 68 00 00 	movl   $0x68,0x10(%esp)
    3881:	00 
    3882:	8b 45 0c             	mov    0xc(%ebp),%eax
    3885:	89 44 24 0c          	mov    %eax,0xc(%esp)
    3889:	8b 45 08             	mov    0x8(%ebp),%eax
    388c:	89 44 24 08          	mov    %eax,0x8(%esp)
    3890:	89 54 24 04          	mov    %edx,0x4(%esp)
    3894:	c7 04 24 00 00 01 00 	movl   $0x10000,(%esp)
    389b:	e8 bc f5 ff ff       	call   0x2e5c
    38a0:	90                   	nop
    38a1:	c9                   	leave  
    38a2:	c2 08 00             	ret    $0x8
    38a5:	90                   	nop
    38a6:	55                   	push   %ebp
    38a7:	89 e5                	mov    %esp,%ebp
    38a9:	83 ec 44             	sub    $0x44,%esp
    38ac:	89 4d bc             	mov    %ecx,-0x44(%ebp)
    38af:	8b 45 bc             	mov    -0x44(%ebp),%eax
    38b2:	83 c0 02             	add    $0x2,%eax
    38b5:	89 45 cc             	mov    %eax,-0x34(%ebp)
    38b8:	8b 45 bc             	mov    -0x44(%ebp),%eax
    38bb:	83 c0 08             	add    $0x8,%eax
    38be:	83 c0 02             	add    $0x2,%eax
    38c1:	89 45 d0             	mov    %eax,-0x30(%ebp)
    38c4:	8b 45 bc             	mov    -0x44(%ebp),%eax
    38c7:	83 c0 10             	add    $0x10,%eax
    38ca:	83 c0 02             	add    $0x2,%eax
    38cd:	89 45 d4             	mov    %eax,-0x2c(%ebp)
    38d0:	8b 45 bc             	mov    -0x44(%ebp),%eax
    38d3:	83 c0 18             	add    $0x18,%eax
    38d6:	83 c0 02             	add    $0x2,%eax
    38d9:	89 45 d8             	mov    %eax,-0x28(%ebp)
    38dc:	8b 45 bc             	mov    -0x44(%ebp),%eax
    38df:	83 c0 48             	add    $0x48,%eax
    38e2:	83 c0 02             	add    $0x2,%eax
    38e5:	89 45 dc             	mov    %eax,-0x24(%ebp)
    38e8:	8b 45 bc             	mov    -0x44(%ebp),%eax
    38eb:	83 c0 4c             	add    $0x4c,%eax
    38ee:	83 c0 02             	add    $0x2,%eax
    38f1:	89 45 e0             	mov    %eax,-0x20(%ebp)
    38f4:	8b 45 bc             	mov    -0x44(%ebp),%eax
    38f7:	83 c0 50             	add    $0x50,%eax
    38fa:	83 c0 02             	add    $0x2,%eax
    38fd:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    3900:	8b 45 bc             	mov    -0x44(%ebp),%eax
    3903:	83 c0 54             	add    $0x54,%eax
    3906:	83 c0 02             	add    $0x2,%eax
    3909:	89 45 e8             	mov    %eax,-0x18(%ebp)
    390c:	8b 45 bc             	mov    -0x44(%ebp),%eax
    390f:	83 c0 58             	add    $0x58,%eax
    3912:	83 c0 02             	add    $0x2,%eax
    3915:	89 45 ec             	mov    %eax,-0x14(%ebp)
    3918:	8b 45 bc             	mov    -0x44(%ebp),%eax
    391b:	83 c0 5c             	add    $0x5c,%eax
    391e:	83 c0 02             	add    $0x2,%eax
    3921:	89 45 f0             	mov    %eax,-0x10(%ebp)
    3924:	8b 45 bc             	mov    -0x44(%ebp),%eax
    3927:	83 c0 60             	add    $0x60,%eax
    392a:	83 c0 02             	add    $0x2,%eax
    392d:	89 45 f4             	mov    %eax,-0xc(%ebp)
    3930:	b8 0b 00 00 00       	mov    $0xb,%eax
    3935:	89 45 f8             	mov    %eax,-0x8(%ebp)
    3938:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
    393f:	8b 45 fc             	mov    -0x4(%ebp),%eax
    3942:	3b 45 f8             	cmp    -0x8(%ebp),%eax
    3945:	74 12                	je     0x3959
    3947:	8b 45 fc             	mov    -0x4(%ebp),%eax
    394a:	8b 44 85 cc          	mov    -0x34(%ebp,%eax,4),%eax
    394e:	66 c7 00 00 00       	movw   $0x0,(%eax)
    3953:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
    3957:	eb e6                	jmp    0x393f
    3959:	8b 45 bc             	mov    -0x44(%ebp),%eax
    395c:	83 c0 64             	add    $0x64,%eax
    395f:	8b 55 bc             	mov    -0x44(%ebp),%edx
    3962:	83 c2 64             	add    $0x64,%edx
    3965:	0f b7 12             	movzwl (%edx),%edx
    3968:	83 e2 01             	and    $0x1,%edx
    396b:	66 89 10             	mov    %dx,(%eax)
    396e:	90                   	nop
    396f:	c9                   	leave  
    3970:	c3                   	ret    
    3971:	90                   	nop
    3972:	55                   	push   %ebp
    3973:	89 e5                	mov    %esp,%ebp
    3975:	83 ec 28             	sub    $0x28,%esp
    3978:	8b 45 08             	mov    0x8(%ebp),%eax
    397b:	c7 44 24 10 68 00 00 	movl   $0x68,0x10(%esp)
    3982:	00 
    3983:	89 44 24 0c          	mov    %eax,0xc(%esp)
    3987:	c7 44 24 08 00 00 01 	movl   $0x10000,0x8(%esp)
    398e:	00 
    398f:	8b 45 10             	mov    0x10(%ebp),%eax
    3992:	89 44 24 04          	mov    %eax,0x4(%esp)
    3996:	8b 45 0c             	mov    0xc(%ebp),%eax
    3999:	89 04 24             	mov    %eax,(%esp)
    399c:	e8 bb f4 ff ff       	call   0x2e5c
    39a1:	8b 4d 08             	mov    0x8(%ebp),%ecx
    39a4:	e8 fd fe ff ff       	call   0x38a6
    39a9:	90                   	nop
    39aa:	c9                   	leave  
    39ab:	c3                   	ret    
    39ac:	45                   	inc    %ebp
    39ad:	6e                   	outsb  %ds:(%esi),(%dx)
    39ae:	74 65                	je     0x3a15
    39b0:	72 65                	jb     0x3a17
    39b2:	64 20 50 72          	and    %dl,%fs:0x72(%eax)
    39b6:	6f                   	outsl  %ds:(%esi),(%dx)
    39b7:	74 65                	je     0x3a1e
    39b9:	63 74 65 64          	arpl   %si,0x64(%ebp,%eiz,2)
    39bd:	20 4d 6f             	and    %cl,0x6f(%ebp)
    39c0:	64 65 2e 0a 00       	fs gs or %cs:(%eax),%al
    39c5:	74 73                	je     0x3a3a
    39c7:	73 30                	jae    0x39f9
    39c9:	20 77 72             	and    %dh,0x72(%edi)
    39cc:	69 74 74 65 6e 0a 00 	imul   $0x48000a6e,0x65(%esp,%esi,2),%esi
    39d3:	48 
    39d4:	61                   	popa   
    39d5:	64 20 6c 74 72       	and    %ch,%fs:0x72(%esp,%esi,2)
    39da:	20 64 6f 6e          	and    %ah,0x6e(%edi,%ebp,2)
    39de:	65 2e 0a 00          	gs or  %cs:(%eax),%al
    39e2:	49                   	dec    %ecx
    39e3:	20 66 65             	and    %ah,0x65(%esi)
    39e6:	65 6c                	gs insb (%dx),%es:(%edi)
    39e8:	20 62 65             	and    %ah,0x65(%edx)
    39eb:	74 74                	je     0x3a61
    39ed:	65 72 20             	gs jb  0x3a10
    39f0:	6e                   	outsb  %ds:(%esi),(%dx)
    39f1:	6f                   	outsl  %ds:(%esi),(%dx)
    39f2:	77 2e                	ja     0x3a22
    39f4:	0a 00                	or     (%eax),%al
    39f6:	43                   	inc    %ebx
    39f7:	68 61 6e 67 69       	push   $0x69676e61
    39fc:	6e                   	outsb  %ds:(%esi),(%dx)
    39fd:	67 20 43 50          	and    %al,0x50(%bp,%di)
    3a01:	4c                   	dec    %esp
    3a02:	20 74 6f 20          	and    %dh,0x20(%edi,%ebp,2)
    3a06:	33 2e                	xor    (%esi),%ebp
    3a08:	0a 00                	or     (%eax),%al
    3a0a:	63 61 6c             	arpl   %sp,0x6c(%ecx)
    3a0d:	6c                   	insb   (%dx),%es:(%edi)
    3a0e:	20 30                	and    %dh,(%eax)
    3a10:	78 32                	js     0x3a44
    3a12:	34 0a                	xor    $0xa,%al
    3a14:	2e 00 00             	add    %al,%cs:(%eax)
    3a17:	00 08                	add    %cl,(%eax)
	...
    3a21:	00 00                	add    %al,(%eax)
    3a23:	00 80 00 00 00 00    	add    %al,0x0(%eax)
    3a29:	00 00                	add    %al,(%eax)
    3a2b:	00 20                	add    %ah,(%eax)
    3a2d:	00 00                	add    %al,(%eax)
    3a2f:	00 10                	add    %dl,(%eax)
    3a31:	00 00                	add    %al,(%eax)
    3a33:	00 08                	add    %cl,(%eax)
    3a35:	00 00                	add    %al,(%eax)
    3a37:	00 38                	add    %bh,(%eax)
    3a39:	00 00                	add    %al,(%eax)
    3a3b:	00 30                	add    %dh,(%eax)
    3a3d:	00 00                	add    %al,(%eax)
    3a3f:	00 28                	add    %ch,(%eax)
    3a41:	00 00                	add    %al,(%eax)
    3a43:	00 18                	add    %bl,(%eax)
    3a45:	00 00                	add    %al,(%eax)
    3a47:	00 00                	add    %al,(%eax)
    3a49:	00 00                	add    %al,(%eax)
    3a4b:	00 04 00             	add    %al,(%eax,%eax,1)
    3a4e:	00 00                	add    %al,(%eax)
    3a50:	02 00                	add    (%eax),%al
    3a52:	00 00                	add    %al,(%eax)
    3a54:	01 00                	add    %eax,(%eax)
    3a56:	00 00                	add    %al,(%eax)
    3a58:	07                   	pop    %es
    3a59:	00 00                	add    %al,(%eax)
    3a5b:	00 06                	add    %al,(%esi)
    3a5d:	00 00                	add    %al,(%eax)
    3a5f:	00 05 00 00 00 03    	add    %al,0x3000000
    3a65:	00 00                	add    %al,(%eax)
    3a67:	00 00                	add    %al,(%eax)
    3a69:	00 00                	add    %al,(%eax)
    3a6b:	00 07                	add    %al,(%edi)
    3a6d:	00 00                	add    %al,(%eax)
    3a6f:	00 19                	add    %bl,(%ecx)
    3a71:	00 00                	add    %al,(%eax)
    3a73:	00 50 00             	add    %dl,0x0(%eax)
    3a76:	00 00                	add    %al,(%eax)
    3a78:	3e 3e 3e 49          	ds ds ds dec %ecx
    3a7c:	6e                   	outsb  %ds:(%esi),(%dx)
    3a7d:	69 74 00 3e 3e 3e 44 	imul   $0x65443e3e,0x3e(%eax,%eax,1),%esi
    3a84:	65 
    3a85:	73 74                	jae    0x3afb
    3a87:	72 6f                	jb     0x3af8
    3a89:	79 00                	jns    0x3a8b
    3a8b:	3e 3e 3e 74 65       	ds ds je,pt 0x3af5
    3a90:	73 74                	jae    0x3b06
    3a92:	00 00                	add    %al,(%eax)
    3a94:	02 00                	add    (%eax),%al
    3a96:	00 00                	add    %al,(%eax)
    3a98:	06                   	push   %es
    3a99:	00 00                	add    %al,(%eax)
    3a9b:	00 02                	add    %al,(%edx)
    3a9d:	00 00                	add    %al,(%eax)
    3a9f:	00 0a                	add    %cl,(%edx)
    3aa1:	00 00                	add    %al,(%eax)
    3aa3:	00 0e                	add    %cl,(%esi)
    3aa5:	00 00                	add    %al,(%eax)
    3aa7:	00 00                	add    %al,(%eax)
    3aa9:	00 00                	add    %al,(%eax)
    3aab:	00 08                	add    %cl,(%eax)
    3aad:	00 00                	add    %al,(%eax)
    3aaf:	00 0a                	add    %cl,(%edx)
    3ab1:	00 00                	add    %al,(%eax)
    3ab3:	00 0d 00 00 00 01    	add    %cl,0x1000000
    3ab9:	00 00                	add    %al,(%eax)
    3abb:	00 03                	add    %al,(%ebx)
    3abd:	00 00                	add    %al,(%eax)
    3abf:	00 09                	add    %cl,(%ecx)
    3ac1:	00 00                	add    %al,(%eax)
    3ac3:	00 0b                	add    %cl,(%ebx)
    3ac5:	00 00                	add    %al,(%eax)
    3ac7:	00 04 00             	add    %al,(%eax,%eax,1)
    3aca:	00 00                	add    %al,(%eax)
    3acc:	0c 00                	or     $0x0,%al
    3ace:	00 00                	add    %al,(%eax)
    3ad0:	05 00 00 00 06       	add    $0x6000000,%eax
    3ad5:	00 00                	add    %al,(%eax)
    3ad7:	00 07                	add    %al,(%edi)
    3ad9:	00 00                	add    %al,(%eax)
    3adb:	00 0e                	add    %cl,(%esi)
    3add:	00 00                	add    %al,(%eax)
    3adf:	00 0f                	add    %cl,(%edi)
    3ae1:	00 00                	add    %al,(%eax)
    3ae3:	00 00                	add    %al,(%eax)
    3ae5:	00 00                	add    %al,(%eax)
    3ae7:	00 01                	add    %al,(%ecx)
    3ae9:	00 00                	add    %al,(%eax)
    3aeb:	00 02                	add    %al,(%edx)
    3aed:	00 00                	add    %al,(%eax)
    3aef:	00 03                	add    %al,(%ebx)
    3af1:	00 00                	add    %al,(%eax)
    3af3:	00 00                	add    %al,(%eax)
    3af5:	06                   	push   %es
    3af6:	00 00                	add    %al,(%eax)
    3af8:	00 05 00 00 00 07    	add    %al,0x7000000
    3afe:	00 00                	add    %al,(%eax)
    3b00:	00 00                	add    %al,(%eax)
    3b02:	00 00                	add    %al,(%eax)
    3b04:	01 00                	add    %eax,(%eax)
	...
