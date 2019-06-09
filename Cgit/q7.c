#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product{
    char num[50];
    char name[50];
    char price[50];
    
    int index_l;
    int num_l;
    int name_l;
    int price_l;
    
    struct product* prev;
    struct product* next;
}pro;

int strcmp(const char *s1, const char *s2);
char *strcpy(char *s1, const char *s2);
int atoi(const char *str);

int GetCharByte(unsigned char* str);
void showResult(pro* result, int index, int numl, int namel, int pricel, int i);
void showSpace(int max, int myself);

int Maxlength(int maxLength, int myLength);
int IndexLength(int index);

int insert(pro* list, pro* insert, char insertList[][20], int iCount);
void update(pro* update, char upList[][20]);
int delete (pro* dl, char deleteList[][20], int i);


int indexL = 2; //NOの表示バイト
int numL = 10;  //コードの表示バイト
int nameL = 6;  //商品名の表示バイト
int priceL =4 ; //単価の表示バイト

int main() {
    FILE* fp;
    int i = 0;
    

    int tl = 0;
    
    int loop = 0;
    
    pro p[10];
    pro* list = p; 
    pro* head = p;
    pro* sw = p;
    
    
    //read csv
    if( (fp = fopen("test.csv","r")) == NULL ) {
        printf("not");
        exit(1);
    }
    
    //先頭の構造体のprevにnull代入
    list->prev = NULL;
    list->next = NULL;
    
    //----------------------
    //csvのデータからリスト生成
    //------------------------

    while( fscanf(fp, "%[^,],%[^,],%s%*c" ,list->num, list->name, list->price) != EOF ) {
        
        //一つ一つの構造体が自身の各コード、商品名、単価の桁数をもつ
        
        //sprintf(list->index, "%d",i+1);
        //list->index_l = GetCharByte(list->index);
        //indexL = Maxlength(indexL, list->index_l);
        
        list->num_l = GetCharByte(list->num);
        numL = Maxlength(numL, list->num_l);
        
        list->name_l = GetCharByte(list->name);
        nameL = Maxlength(nameL, list->name_l);
        
        list->price_l = GetCharByte(list->price);
        priceL = Maxlength(priceL, list->price_l);

   
        //csvから読み込んだデータをまず連結
        if(i == 0) {
            list->next = NULL; 
        }
        //Bのとき
        else {
            list->prev = head;  //BのprevAを代入
            head = list;
            list->prev->next = list; //Aのnextに代入
            list->next = NULL;
        }
        
        list++;
        i++;
    }

    
    //--------------------------------------------
    //出力処理
    //--------------------------------------------
    showResult(sw, indexL, numL, nameL, priceL,i);
    
    //--------------------------------------------
    //入力処理
    //--------------------------------------------


   //char inList[4][20] = {{"insert"},{"00002"},{"追加"},{"10000000"}};
   //char upList[4][20] = {{"update"},{"00004"},{"price"},{"700"}};
   char dlList[2][20] = {{"delete"},{"00004"}};
   
   /*
   if(strcmp(upList[0],"insert") == 0) {
       insert(list, sw, upList, i);
   }
   else if(strcmp(upList[0],"update") == 0) {
       update(sw, upList);
   }
   else if(strcmp(upList[0],"delete") == 0) {
        delete(sw,upList);
   }*/
   
   sw = p;
   //i = insert(list, sw, inList, i);
   //update(sw, upList);
   i = delete(sw, dlList, i);


   showResult(sw, indexL, numL, nameL, priceL,i);
   fclose(fp);
   return 0;
}


int insert(pro* list, pro* insert, char insertList[][20], int iCount) {
    
     //追加する構造体の生成
     strcpy(list->num,insertList[1]);
     strcpy(list->name,insertList[2]);
     strcpy(list->price,insertList[3]);

     iCount++;

    list->num_l = GetCharByte(list->num);
    numL = Maxlength(numL, list->num_l);

    list->name_l = GetCharByte(list->name);
    nameL = Maxlength(nameL, list->name_l);

    list->price_l = GetCharByte(list->price);
    priceL = Maxlength(priceL, list->price_l);

     //生成した構造体を双方向リストに結合
     while(1) {
         if(atoi(insert->num) > atoi(insertList[1]) ) {
             
             //構造体Cのprevと構造体Bのprev更新
             insert->prev = list;
             list->next = insert;
             
             
             //構造体Cのprevと構造体Bのnext更新
             insert--;
             insert->next = list;
             list->prev = list; 
             break;
         } 
         insert++;
     }
     
     return iCount;
}


void update(pro* update, char upList[][20]) {
    
   while(update->next != NULL) {
       //更新する商品コードと同じコードがある場合にtrue
       if(atoi(update->num) == atoi(upList[1])) {
           if(strcmp(upList[2],"num") == 0) {
                strcpy(update->num,upList[3]);
           }
           else if(strcmp(upList[2],"name") == 0) {
                strcpy(update->name,upList[3]);
           }
           else if(strcmp(upList[2],"price") == 0) {
               strcpy(update->price,upList[3]);
           }
       }
       update++;
    }
}

 //delete(sw, dlList);
int delete (pro* dl, char deleteList[][20],int i) {
     while(1){
         
         if( atoi(dl->num) == atoi(deleteList[1]) ) {

             //n-1の構造体のnextにn+1の構造体のアドレスを代入
             dl->prev->next = dl->next;
            // dl->next = NULL;
             
             
             //n+1の構造体のprevにn-1の構造体のアドレスを代入
             dl->next->prev = dl->prev;
             //dl->prev = NULL;
             i--;
             return i; 
         } 
         else if (dl->next == NULL) {
            break;
         } 
         dl++;
     }
 }

int GetCharByte(unsigned char* str)
{
    int cnt = 0;
        int i = 0;
	for (i; str[i] != '\0'; ){ //ここでは増減処理[i++]は行わない
		if (str[i] >= 0x00 && str[i] <= 0x7F) { //1byte文字
                        //printf("%s\n", &str[i]);
                        i += 1; //1byte分進む
                        cnt += 1;
		} else if (str[i] >= 0xC0 && str[i] <= 0xDF) { //2byte文字
			i += 2; //2byte分進む
                        cnt += 2;
                        //printf("oo\n");
		} else if (str[i] >= 0xE0 && str[i] <= 0xEF) { //3byte文字
			i += 3; //3byte分進む
                        cnt += 2;
                        //printf("ooo\n");
		} else if (str[i] >= 0xF0 && str[i] <= 0xF7) { //4byte文字
			i += 4; //4byte分進む
		} else if (str[i] >= 0xF8 && str[i] <= 0xFB) { //5byte文字
			i += 5; //5byte分進む                        
		} else if (str[i] >= 0xFC && str[i] <= 0xFD) { //6byte文字
			i += 6; //6byte分進む                    
		} else {
			i += 1; //該当なしの場合1byte分進む（無限ループ回避のため）
		}
	}
	return cnt;
}




void showResult(pro* result, int index, int numl, int namel, int pricel,int i)
{
    int loop = 0;
    int totalLength = index + numl + namel + pricel;
    for(loop = 0; loop < i + 1; loop++) {
        //ヘッダ表示
        if(loop == 0) {
            printf("NO");
            showSpace(index, 2);
            printf("|");

            printf("商品コード");  
            showSpace(numl,10);
            printf("|");

            printf("商品名");
            showSpace(namel,6);
            printf("|");

            showSpace(pricel, 4);
            printf("単価");
            printf("|\n");

            for(loop; loop < totalLength + 4; loop++ ){
                printf("-");
            }
            printf("\n");
            loop = 0;
        }
        else {
            //No表示
            printf("%d",loop);
            showSpace(index, IndexLength(loop));
            printf("|");

            //コード表示
            printf("%s",result->num);
            showSpace(numl, result->num_l);
            printf("|");

            //商品名表示
            printf("%s",result->name);
            showSpace(namel, result->name_l);
            printf("|");

            //単価表示(右揃え)
            showSpace(pricel, result->price_l);
            printf("%s",result->price);
            printf("|\n");
            
            result = result->next;
        }   
    }
}

void showSpace(int max, int myself) 
{
    int iCount = max - myself;
    
    while (iCount != 0) {
        printf(" ");
        iCount--;
    }
}

int Maxlength(int maxLength, int myLength) {
    if(maxLength < myLength) {
        maxLength = myLength;
    }
    return maxLength;
}

int IndexLength(int index) {
    int cnt = 0;
    while(index != 0) {
        index = index / 10;
        cnt++;
    }
    return cnt;
}