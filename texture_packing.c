#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_WIDTH 100
#define MAX_NUM 10000

typedef struct texture{
    int width;
    int height;
}Texture;

typedef struct shell{
    int lefted_width;
    int height;
}Shell;

typedef struct shell_set{
    Shell *shell;
    int count;
}Shell_set;

void push(Shell_set* shell_set,Texture* texture){
    int havs_puted=0;
    for(int i=0;i<shell_set->count;i++){
        if(texture->width < shell_set->shell[i].lefted_width){
            shell_set->shell[i].lefted_width=shell_set->shell[i].lefted_width-texture->width;
            havs_puted=1;
            break;
        }
    }

    if(!havs_puted){
        /* 没找到合适的已有 shell，创建一个新 shell 并减少剩余宽度 */
        shell_set->shell[shell_set->count].lefted_width = MAX_WIDTH - texture->width;
        shell_set->shell[shell_set->count].height = texture->height;
        shell_set->count++;
    }
}

int compared_by_lefted_width(const void *a,const void * b ){
    const Shell *shell_a=(const Shell*)a;
    const Shell *shell_b=(const Shell*)b;
    return shell_a->lefted_width - shell_b->lefted_width;
}

int compared_by_height(const void *a,const void * b ){
    const Texture *texture_a=(const Texture*)a;
    const Texture *texture_b=(const Texture*)b;
    return texture_b->height - texture_a->height;
}

int main(){
    int n;
    printf("the first line is the number of textures:\n");
    printf("the following lines are the width and height of each texture:\n");
    printf("you should print like \n 1\n 2 4\n");
    scanf("%d",&n);
    Texture* textures=(Texture*)malloc(sizeof(Texture)*n);
    for(int i=0;i<n;i++){
        scanf("%d %d",&textures[i].width,&textures[i].height);
    }

    qsort(textures,n,sizeof(Texture),compared_by_height);

    Shell_set shell_set;
    shell_set.shell=(Shell*)malloc(sizeof(Shell)*MAX_NUM);
    shell_set.count=0;

    for(int i=0;i<n;i++){
        push(&shell_set,&textures[i]);
        qsort(shell_set.shell,shell_set.count,sizeof(Shell),compared_by_lefted_width);
    }

    int height_sum=0;
    for(int i=0;i<shell_set.count;i++){
        height_sum+=shell_set.shell[i].height;
    }

    printf("%d\n",height_sum);
    printf("%d\n",shell_set.count);
    free(textures);
    free(shell_set.shell);
    return 0;
}