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
void showResult(pro* result);
void showSpace(int max, int myself);

int Maxlength(int maxLength, int myLength);
int IndexLength(int index);

pro* insert(pro* adhead, pro* head, char insertList[][20]);
pro* update(pro* update, char upList[][20], char inList[][20]);
pro* delete (pro* dl, char deleteList[][20]);


int indexL = 2; //NOの表示バイト
int numL = 10;  //コードの表示バイト
int nameL = 6;  //商品名の表示バイト
int priceL =4 ; //単価の表示バイト
int iIndexCount = 0;

int main() {
    FILE* fp;
    

    //pro p[10];
    pro* list = (pro*)malloc(sizeof(pro)); 
    pro* head = list;
    pro* sw = list;
    pro* tmp = list;
    
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
        

        list->num_l = GetCharByte(list->num);
        numL = Maxlength(numL, list->num_l);
        
        list->name_l = GetCharByte(list->name);
        nameL = Maxlength(nameL, list->name_l);
        
        list->price_l = GetCharByte(list->price);
        priceL = Maxlength(priceL, list->price_l);
    
        //csvから読み込んだデータをまず連結
        
        if(iIndexCount > 0) {
        
            list->prev = head;  //BのprevAを代入
            head->next = list;
            head = list;
        }
        
        list->next = (pro*)malloc(sizeof(pro));
        list = list->next;
        iIndexCount++;
    }
    

    list->next = NULL;
    //free(list);
   


    //--------------------------------------------
    //出力処理
    //--------------------------------------------
    //showResult(sw);
    
    //--------------------------------------------
    //入力処理
    //--------------------------------------------


   char inList[4][20] = {{"insert"},{"00000"},{"aaaaaaaaaa"},{"10000000"}};
   char inList2[4][20] = {{"insert"},{"00001"},{"bbbbbbbb"},{"10000000"}};
   
   char upList[4][20] = {{"update"},{"00004"},{"price"},{"700"}};
   char upList2[4][20] = {{"update"},{"00004"},{"num"},{"00007"}};
   char upList3[4][20] = {{"update"},{"00005"},{"num"},{"00008"}};


   
   
   char dlList[2][20] = {{"delete"},{"00003"}};
   char dlList2[2][20] = {{"delete"},{"00004"}};
   

 
   
   
//insert
   
   printf("%p\n",tmp);
   printf("%p\n",sw);
   tmp = insert(tmp, sw, inList);
   iIndexCount++;
   showResult(tmp);

   printf("%p\n",tmp);
   printf("%p\n",sw);
   
   //tmp = insert(tmp, sw, inList2);  
   //iIndexCount++;
   //showResult(tmp);
  
 

   
 /*delete
   tmp = delete(tmp,dlList);
   showResult(tmp);
   
      
   tmp = delete(tmp,dlList2);
   showResult(tmp);
*/ 

   
   //tmp = update(tmp, upList2, inList);
   //showResult(tmp);
   
 
   //tmp = update(tmp, upList3, inList2);
   //showResult(tmp);
   
   fclose(fp);
   return 0;
}



pro* insert(pro* adhead, pro* head, char insertList[][20]) {
    
    
    pro* tmpad = adhead;
    //list = tmp

    
    //領域確保
    while(head->next != NULL) {
        
        head = head->next;
    }
    head->next = (pro*)malloc(sizeof(pro)); 
    head = head->next;
    head->next = NULL;
    
    
    
    
     //追加する構造体の生成
     strcpy(head->num,insertList[1]);
     strcpy(head->name,insertList[2]);
     strcpy(head->price,insertList[3]);

     

    head->num_l = GetCharByte(head->num);
    numL = Maxlength(numL, head->num_l);

    head->name_l = GetCharByte(head->name);
    nameL = Maxlength(nameL, head->name_l);

    head->price_l = GetCharByte(head->price);
    priceL = Maxlength(priceL, head->price_l);
    
    
    //先頭に追加する場合
    if(atoi(adhead->num) > atoi(head->num) ){
        
        //新しい構造体が先頭に
        head->prev = NULL;
        head->next = adhead;
        
        //先頭だった構造体を2番目に
        adhead->prev = head;
        
        
        //showは先頭のnextから表示
        return head;
         
    }
    //末尾に追加

    
     //生成した構造体を双方向リストに結合
     while(1) {
         //間に挿入
         if(atoi(adhead->num) > atoi( head->num) ) {
            //n-1の構造体
             adhead->prev->next = head;
             
             //追加する構造体
             head->prev = adhead->prev;
             head->next = adhead->next;
             
             //n+1の構造体
             adhead->prev = head;
             break;

         } 
         //末尾に挿入
         else if(adhead->next == NULL) {
             
             adhead->next = head;
             
             head->prev = adhead;
             head->next = NULL;
             
             break;
         } 
         //上書きはエラー
         else if(adhead->num == head->num) {
             printf("すでに存在。\n");
             break;
         }
         
         //次の構造体へ
         adhead = adhead->next;
     }
     
     return adhead;
}


pro* update(pro* update, char upList[][20], char inList[][20]) {
    
    pro* tmpup = update;
    pro* tmpuphead = update;
    
    //char inList3[4][20] = {{"insert"},{"00007"},{"消しゴム"},{"500"}};
    
    //char upList[4][20] = {{"update"},{"00004"},{"price"},{"700"}};
    
    
   while(update->next != NULL) {
       
       
       //更新する商品コードと同じコードがある場合にtrue
       if(atoi(update->num) == atoi(upList[1])) {
           
           
           
           if(strcmp(upList[2],"num") == 0) {
               //既存の商品コードを削除
               
               tmpup = delete(tmpup, upList);
               iIndexCount++;
               tmpup = insert(tmpup, tmpuphead, inList);
               return tmpup;
               
           }
           else if(strcmp(upList[2],"name") == 0) {
                strcpy(update->name,upList[3]);
                return tmpup;
           }
           else if(strcmp(upList[2],"price") == 0) {
               strcpy(update->price,upList[3]);
               return tmpup;
           }
       }
       
       
       
       update = update->next;
    }
}



 //delete(sw, dlList);
pro* delete (pro* dl, char deleteList[][20]) {
    
    pro* tmpdl = dl;
    
     while(1){
         
         if( atoi(dl->num) == atoi(deleteList[1]) ) {
             
             //先頭を削除
             if(dl->prev == NULL) {
                 dl->next->prev = NULL;
                 iIndexCount--;
                 return dl->next;       
             }
             
             //末尾を削除
             else if(dl->next == NULL) {
                 dl->prev->next = NULL;
                 iIndexCount--;
                 return tmpdl;
             }
             
             //間の構造体を削除
             else {
                 dl->prev->next = dl->next;
                 dl->next->prev = dl->prev;
                 iIndexCount--;
                 return tmpdl;
             }
             
         } else if(dl->next == NULL) {
             printf("指定したコードは存在しません。\n");
             return tmpdl;
         }
         dl = dl->next;
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




void showResult(pro* result)
{
    int loop = 0;
    int totalLength = indexL + numL + nameL + priceL;
    for(loop = 0; loop < iIndexCount + 1; loop++) {
        //ヘッダ表示
        if(loop == 0) {
            printf("NO");
            showSpace(indexL, 2);
            printf("|");

            printf("商品コード");  
            showSpace(numL,10);
            printf("|");

            printf("商品名");
            showSpace(nameL,6);
            printf("|");

            showSpace(priceL, 4);
            printf("単価");
            printf("|\n");

            for(loop=0; loop < totalLength + 4; loop++ ){
                printf("-");
            }
            printf("\n");
            loop = 0;
        }
        else {
            //No表示
            printf("%d",loop);
            showSpace(indexL, IndexLength(loop));
            printf("|");

            //コード表示
            printf("%s",result->num);
            showSpace(numL, result->num_l);
            printf("|");

            //商品名表示
            printf("%s",result->name);
            showSpace(nameL, result->name_l);
            printf("|");

            //単価表示(右揃え)
            showSpace(priceL, result->price_l);
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