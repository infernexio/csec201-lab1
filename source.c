#include<stdio.h>
#include<string.h>
#include<ctype.h>

int get_enc_dec(){
    int enc_dec;
    printf("Enter 1 to encrypt, 2 to decrypt: ");
    scanf("%d", &enc_dec);
    return enc_dec;
}

void encode(char *input, char *encodeAlpha, char* decodeAlpha){
    char output[100] = {0};
    int i = 0;
    int found = 0;
    while(input[i] != '\0'){
        if(input[i] != ' '){
            for(int j = 0; j < 26; j++){
                if(toupper(input[i]) == toupper(decodeAlpha[j])){
                    output[i] = encodeAlpha[j];
                    found = 1;
                }
            }
        }else{
            output[i] = ' ';
            found = 1;
        }

        found = 0;
        i++;
    }
    puts(output);
}

void decode(char *input, char *decodeAlpha, char* encodeAlpha){
    char output[100] = {0};
    int i = 0;
    int found = 0;
    while(input[i] != '\0'){
        if(input[i] != ' '){
            for(int j = 0; j < 26; j++){
                if(toupper(input[i]) == toupper(encodeAlpha[j])){
                    output[i] = decodeAlpha[j];
                    found = 1;
                }
            }
        }else{
            output[i] = ' ';
            found = 1;
        }
        found = 0;
        i++;
    }

    puts(output);
}

int main(int argc, char *argv[]){
    char encodingAlfa[26] = {0};
    char decodingAlfa[26] = {0};

    FILE* handle;
    char line[10] = {0};
    int i = 0;

    if(argc == 2){
        handle = fopen(argv[1], "r");

        while (fgets(line, 10, handle)){
            if(line[0] != '\n'  && line[2] != '\n'){
                if(strchr(encodingAlfa, toupper(line[2])) == NULL &&
                        strchr(decodingAlfa, toupper(line[0])) == NULL){
                    encodingAlfa[i] = toupper(line[2]);
                    decodingAlfa[i] = toupper(line[0]);
                }else{
                    puts("Error: Duplicate character in cipher text");
                    return 1;
                }
            }else{
                puts("Error: a pair not complete in cipher text");
                puts("continuing...");
            }
            i++;
        }
        fclose(handle);    

        /* test print for encodingAlfa and decodingAlfa
        for(int i=0; i<26; i++){
            printf("%c\t", encodingAlfa[i]);
            printf("%c\n", decodingAlfa[i]);
        }
        */

        char input[100] = {0};
        int enc_dec;

        printf("Enter a string: ");
        fgets(input, 100, stdin);

        enc_dec = get_enc_dec();

        if(enc_dec == 1){
            encode(input, encodingAlfa, decodingAlfa);
        }else if(enc_dec == 2){
            decode(input, decodingAlfa, encodingAlfa);
        }else{
            printf("%d is not a valid option\n please try again", enc_dec);
        }
    }else{
        puts("Error: file not found");
    }

    return 0;
}