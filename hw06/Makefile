CC = gcc # c 컴파일러를 이용하겠다는 의미
CFLAGS = #컴파일 옵션
LDFLAGS = -lpthread #링킹 옵션pthread라는 라이브러리를 링킹하겠다는 의미
#.c와.o 확장자를 가진 파일들을 확장자 규칙에 의거해서 처리되도록 한다
.SUFFIXES : .c .o
.c.o : #미리 정의된 suffixes룰에 의해서 .o파일이 타깃으로 오면 .c파일로 컴파일한다
	$(CC) -c $(CFLAGS) $<
#.c파일을 .o로 컴파일을 하는데 컴파일옵션인 CFLAGS를 이용하고 $<는 현재 prerequisite 를 의미하며 여기서는 .c 파일이 들어간다
ALL = sig1 sig2 mysleep alarm nonreent sig_thread cancel
#all이라는 타깃이 오면 미리 정의했던 ALL에 있는 것들을 prerequisites로 받는다
all: $(ALL)
#sig1가 타겟으로 오면 prerequisite에 sig1.o을 대입한다.
sig1: sig1.o
	$(CC) -o $@ $< $(LDFLAGS)
#아래는 위에와 동일하게 동작
sig2: sig2.o
	$(CC) -o $@ $< $(LDFLAGS)

mysleep: mysleep.o
	$(CC) -o $@ $< $(LDFLAGS)

alarm: alarm.o
	$(CC) -o $@ $< $(LDFLAGS)

nonreent: nonreent.o
	$(CC) -o $@ $< $(LDFLAGS)

sig_thread: sig_thread.o
	$(CC) -o $@ $< $(LDFLAGS)

cancel: cancel.o
	$(CC) -o $@ $< $(LDFLAGS)
#clean이라는 타깃이 오면 .o파일과 ALL 파일들을 모두 강제로 삭제한다
clean :
	rm -rf *.o $(ALL)
