struct X{
        char x;
        int y;
};

struct Y{
        char x;
        int y;
} __attribute__((packed));
int a=sizeof(struct X);
int b=sizeof(struct Y);

