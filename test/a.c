
int f(int num){return num+2;}

int main(int argc, char** argv){

    int(*fp)(int) = f;
    f(2);

    return 0;
}
