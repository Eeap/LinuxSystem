CC = gcc# c 컴파일러를 이용하겠다는 의미
CFLAGS =#컴파일 옵션
LDFLAGS = -lpthread#링킹 옵션 pthread를 링킹함.
#.c와.o 확장자를 가진 파일들을 확장자 규칙에 의거해서 처리되도록 한다
.SUFFIXES : .c .o
.c.o :#미리 정의된 suffixes룰에 의해서 .o파일이 타깃으로 오면 .c파일로 컴파일한다
	$(CC) -c $(CFLAGS) $<
#.c파일을 .o로 컴파일을 하는데 컴파일옵션인 CFLAGS를 이용하고 $<는 현재 prerequisite 를 의미하며 여기서는 .c 파일이 들어간다
ALL = producer consumer producer_s consumer_s prodcons dining dining2 prodcons_m prodcons_s sipc1_s sipc2_s sipc_t_m sipc_t_s
#all이라는 타깃이 오면 미리 정의했던 ALL에 있는 것들을 prerequisites로 받는다
all: $(ALL)
#prodcons_t가 타겟으로 오면 prerequisite에 prodcons_t.o을 대입한다.
prodcons_t: prodcons_t.o
	$(CC) -o $@ $< $(LDFLAGS)

producer: producer.o 
	$(CC) -o $@ $< $(LDFLAGS)

consumer: consumer.o 
	$(CC) -o $@ $< $(LDFLAGS)

producer_s: producer_s.o semlib.o
	$(CC) -o $@ $^ $(LDFLAGS)

consumer_s: consumer_s.o semlib.o
	$(CC) -o $@ $^ $(LDFLAGS)

prodcons: prodcons.o
	$(CC) -o $@ $< $(LDFLAGS)

dining: dining.o
	$(CC) -o $@ $< $(LDFLAGS)

dining2: dining2.o
	$(CC) -o $@ $< $(LDFLAGS)

prodcons_m: prodcons_m.o
	$(CC) -o $@ $< $(LDFLAGS)

prodcons_s: prodcons_s.o semlib2.o
	$(CC) -o $@ $^ $(LDFLAGS)

sipc_t_m: sipc_t_m.o
	$(CC) -o $@ $^ $(LDFLAGS)

sipc_t_s: sipc_t_s.o
	$(CC) -o $@ $^ $(LDFLAGS)

sipc1_s: sipc1_s.o semlib.o
	$(CC) -o $@ $^ $(LDFLAGS)

sipc2_s: sipc2_s.o semlib.o
	$(CC) -o $@ $^ $(LDFLAGS)
#clean이라는 타깃이 오면 .o파일과 ALL 파일들을 모두 강제로 삭제한다
clean :
	rm -rf *.o $(ALL)
