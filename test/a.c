
int f(int num){return num+2;}
const char a = 'a';
static char b = 'b';
int c = 10;

int main(int argc, char** argv){

    int(*fp)(int) = f;
    f(2);

    return 0;
}
