#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {

    char okunan[255] = {}; // Okunan metnin karakterlerinin kopyalanacaðý char array.
    char karakter, temp;
    int i = 0, stringTirnagi = 0, yorumBasladi = 0, yorumBitti = 0, identifierUzunlugu = 0, intUzunlugu = 0;

    FILE *dosya1;
    if ((dosya1 = fopen("code.psi.txt","r")) == NULL) printf("dosya okumada hata var");
    else {

        while (!feof(dosya1)){

            karakter = fgetc(dosya1);

// Dosyadaki metinden okunan karakterin uzun harf olup olmadýðý kontrol edilir, uzunsa kýsa hali *karakter* deðiþkenine atanýr.

            if (isupper(karakter)) {

                temp = karakter;
                karakter = tolower(temp);
            }

// Okunan metindeki karakterler teker teker *okunan* char array'ine kopyalanýr.

            okunan[i] = karakter;
            i++;
        }
        fclose(dosya1);
    }

    dosya1 = fopen("code.lex.txt","w");

// *okunan* char array'indeki karakterler teker teker kontrol edilip, uygun token þeklinde code.lex dosyasýna yazýlýr.

    for (i = 0; i < strlen(okunan); i++) {

        if (okunan[i] == '"') {

// Okunan string týrnaðý sayýsýnýn çift veya tek olmasýna göre string'in bitip bitmediði belirlenir.

            stringTirnagi++;

            if (stringTirnagi % 2 != 0) {
                fputs("StringConst(",dosya1);
            }
            else {
                fputc(okunan[i],dosya1);
                fputs(")\n",dosya1);
            }
        }

        if (stringTirnagi % 2 != 0) {
            fputc(okunan[i],dosya1);
        }

// Kapanmamýþ bir string yoksa, geri kalan token'lara geçilir.

        else {

// Boþluða karþýlýk gelen karakterler atlanýr.

            if (isspace(okunan[i])) continue;

// Okunan metin içerisinde comment olup olmadýðý, varsa kapanana kadar comment içinde olan kýsmýn atlanacaðý *yorumBasladi* ve *yorumBitti*
// deðiþkenlerinin sayýlarýnýn birbirine eþit olup olmamasýna bakýlarak belirlenir.

            if (okunan[i] == '(' && okunan[i+1] == '*') {
                yorumBasladi++;
            }
            else if (okunan[i] == ')' && okunan[i-1] == '*') {
                yorumBitti++;
                continue;
            }
            if (yorumBasladi != yorumBitti) {
                continue;
            }
// Okunan mevcut index'teki karakterin ve gelecek index'lerdeki karakterlerin neye karþýlýk geldiði kontrol edilip, keyword token'ý oluþturulur.

            if (okunan[i] == 'b' && okunan[i+1] == 'r' && okunan[i+2] == 'e' && okunan[i+3] == 'a' && okunan[i+4] == 'k' && ispunct(okunan[i+5]) &&
                okunan[i+5] != '_') {
                fputs("Keyword(break)\n",dosya1);
                i += 4;
                continue;
            }
            else if (okunan[i] == 'c' && okunan[i+1] == 'a' && okunan[i+2] == 's' && okunan[i+3] == 'e' && ispunct(okunan[i+4]) &&
                okunan[i+4] != '_') {
                fputs("Keyword(case)\n",dosya1);
                i += 3;
                continue;
            }
            else if (okunan[i] == 'c' && okunan[i+1] == 'h' && okunan[i+2] == 'a' && okunan[i+3] == 'r' && ispunct(okunan[i+4]) &&
                okunan[i+4] != '_') {
                fputs("Keyword(char)\n",dosya1);
                i += 3;
                continue;
            }
            else if (okunan[i] == 'c' && okunan[i+1] == 'o' && okunan[i+2] == 'n' && okunan[i+3] == 's' && okunan[i+4] == 't' &&
                     ispunct(okunan[i+5]) && okunan[i+5] != '_') {
                fputs("Keyword(const)\n",dosya1);
                i += 4;
                continue;
            }
            else if (okunan[i] == 'c' && okunan[i+1] == 'o' && okunan[i+2] == 'n' && okunan[i+3] == 't' && okunan[i+4] == 'i' &&
                     okunan[i+5] == 'n' && okunan[i+6] == 'u' && okunan[i+7] == 'e' && ispunct(okunan[i+8]) && okunan[i+8] != '_') {
                fputs("Keyword(continue)\n",dosya1);
                i += 7;
                continue;
            }
            else if (okunan[i] == 'd' && okunan[i+1] == 'o'  && ispunct(okunan[i+2]) && okunan[i+2] != '_') {
                fputs("Keyword(do)\n",dosya1);
                i += 1;
                continue;
            }
            else if (okunan[i] == 'e' && okunan[i+1] == 'l' && okunan[i+2] == 's' && okunan[i+3] == 'e'  && ispunct(okunan[i+4]) &&
                okunan[i+4] != '_') {
                fputs("Keyword(else)\n",dosya1);
                i += 3;
                continue;
            }
            else if (okunan[i] == 'e' && okunan[i+1] == 'n' && okunan[i+2] == 'u' && okunan[i+3] == 'm' && ispunct(okunan[i+4]) &&
                okunan[i+4] != '_') {
                fputs("Keyword(enum)\n",dosya1);
                i += 3;
                continue;
            }
            else if (okunan[i] == 'f' && okunan[i+1] == 'l' && okunan[i+2] == 'o' && okunan[i+3] == 'a' && okunan[i+4] == 't'  &&
                     ispunct(okunan[i+5]) && okunan[i+5] != '_') {
                fputs("Keyword(float)\n",dosya1);
                i += 4;
                continue;
            }
            else if (okunan[i] == 'f' && okunan[i+1] == 'o' && okunan[i+2] == 'r' && ispunct(okunan[i+3]) && okunan[i+3] != '_') {
                fputs("Keyword(for)\n",dosya1);
                i += 2;
                continue;
            }
            else if (okunan[i] == 'g' && okunan[i+1] == 'o' && okunan[i+2] == 't' && okunan[i+3] == 'o' && ispunct(okunan[i+4]) &&
                okunan[i+4] != '_') {
                fputs("Keyword(goto)\n",dosya1);
                i += 3;
                continue;
            }
            else if (okunan[i] == 'i' && okunan[i+1] == 'f' && ispunct(okunan[i+2]) && okunan[i+2] != '_') {
                fputs("Keyword(if)\n",dosya1);
                i += 1;
                continue;
            }
            else if (okunan[i] == 'i' && okunan[i+1] == 'n' && okunan[i+2] == 't' && ispunct(okunan[i+3]) && okunan[i+3] != '_') {
                fputs("Keyword(int)\n",dosya1);
                i += 2;
                continue;
            }
            else if (okunan[i] == 'l' && okunan[i+1] == 'o' && okunan[i+2] == 'n' && okunan[i+3] == 'g'  && ispunct(okunan[i+4]) &&
                okunan[i+4] != '_') {
                fputs("Keyword(long)\n",dosya1);
                i += 3;
                continue;
            }
            else if (okunan[i] == 'r' && okunan[i+1] == 'e' && okunan[i+2] == 'c' && okunan[i+3] == 'o' && okunan[i+4] == 'r' &&
                     okunan[i+5] == 'd'  && ispunct(okunan[i+6]) && okunan[i+6] != '_') {
                fputs("Keyword(record)\n",dosya1);
                i += 5;
                continue;
            }
            else if (okunan[i] == 'r' && okunan[i+1] == 'e' && okunan[i+2] == 't' && okunan[i+3] == 'u' && okunan[i+4] == 'r' &&
                     okunan[i+5] == 'n'  && ispunct(okunan[i+6]) && okunan[i+6] != '_') {
                fputs("Keyword(return)\n",dosya1);
                i += 5;
                continue;
            }
            else if (okunan[i] == 's' && okunan[i+1] == 't' && okunan[i+2] == 'a' && okunan[i+3] == 't' && okunan[i+4] == 'i' &&
                     okunan[i+5] == 'c'  && ispunct(okunan[i+6]) && okunan[i+6] != '_') {
                fputs("Keyword(static)\n",dosya1);
                i += 5;
                continue;
            }
            else if (okunan[i] == 'w' && okunan[i+1] == 'h' && okunan[i+2] == 'i' && okunan[i+3] == 'l' && okunan[i+4] == 'e'  &&
                     ispunct(okunan[i+5]) && okunan[i+5] != '_') {
                fputs("Keyword(while)\n",dosya1);
                i += 4;
                continue;
            }

// Okunan karakterin harf ile baþlayýp; harf, sayý veya alt çizgi ile devam ettiði kontrol edilerek identifier token'ý oluþturulur.

            if (islower(okunan[i]) && identifierUzunlugu == 0) {
                fputs("Identifier(",dosya1);
                fputc(okunan[i],dosya1);
                identifierUzunlugu++;
                continue;
            }

            if (okunan[i] == '_') {
                fputc(okunan[i],dosya1);
                identifierUzunlugu++;
                continue;
            }

            if (islower(okunan[i]) || isdigit(okunan[i]) && identifierUzunlugu != 0) {
                fputc(okunan[i],dosya1);
                identifierUzunlugu++;
                continue;
            }

// Identifier 20 karakterden fazla ise konsola hata yazdýrýlýr.

            if (identifierUzunlugu != 0) {
                if (identifierUzunlugu > 20) {
                    printf("Lexical Analiz Hatasi. 20 karakterden uzun identifier.\n");
                }
                fputs(")\n",dosya1);
                identifierUzunlugu = 0;
            }

// Okunan ve identifier'a baðlý olmayan karakterlerin sayý olup olmadýðý kontrol edilerek, int constant token'ý oluþturulur.

            if (isdigit(okunan[i]) && intUzunlugu == 0) {
                fputs("IntConst(",dosya1);
                fputc(okunan[i],dosya1);
                intUzunlugu++;
                continue;
            }

            if (isdigit(okunan[i])) {
                fputc(okunan[i],dosya1);
                intUzunlugu++;
                continue;
            }

// Int constant 10 karakterden fazla ise konsola hata yazdýrýlýr.

            if (intUzunlugu != 0) {
                if (intUzunlugu > 10) {
                    printf("Lexical Analiz Hatasi. 20 karakterden uzun integer.\n");
                }
                fputs(")\n",dosya1);
                intUzunlugu = 0;
            }

// Okunan karakter string'e, comment'e, identifier’a veya int constant’a ait deðilse, hangi operatör olduðu kontrol edilir ve ve kontrole göre
// operatör token'ýna veya parantez token'larýndan birine atanýr.

            if (okunan[i] == '+' && okunan[i+1] == '+') {
                fputs("Operator(++)\n",dosya1);
            }
            else if (okunan[i] == '+' && okunan[i-1] != '+') {
                fputs("Operator(+)\n",dosya1);
            }
            else if (okunan[i] == '-' && okunan[i+1] == '-') {
                fputs("Operator(--)\n",dosya1);
            }
            else if (okunan[i] == '-' && okunan[i-1] != '-') {
                fputs("Operator(-)\n",dosya1);
            }
            else if (okunan[i] == '*') {
                fputs("Operator(*)\n",dosya1);
            }
            else if (okunan[i] == '/') {
                fputs("Operator(/)\n",dosya1);
            }
            else if (okunan[i] == ':' && okunan[i+1] == '=') {
                fputs("Operator(:=)\n",dosya1);
            }
            else if (okunan[i] == ';') {
                fputs("EndOfLine\n",dosya1);
            }
            else if (okunan[i] == '(') {
                fputs("LeftPar\n",dosya1);
            }
            else if (okunan[i] == ')') {
                fputs("RightPar\n",dosya1);
            }
            else if (okunan[i] == '[') {
                fputs("LeftSquareBracket\n",dosya1);
            }
            else if (okunan[i] == ']') {
                fputs("RightSquareBracket\n",dosya1);
            }
            else if (okunan[i] == '{') {
                fputs("LeftCurlyBracket\n",dosya1);
            }
            else if (okunan[i] == '}') {
                fputs("RightCurlyBracket\n",dosya1);
            }
        }
    }

    fclose(dosya1);

// String týrnaðý sayýsýnýn tek olup olmadýðý kontrol edilir, eðer tekse kapatýlmadýðý anlaþýlýp konsola hata yazdýrýlýr.

    if (stringTirnagi % 2 != 0) {
        printf("Lexical Analiz Hatasi. Kapatilmamis string.\n");
    }

// *yorumBasladi* ve *yorumBitti* deðiþkenlerinin sayý deðerlerinin birbirine eþit olup olmadýðý karþýlaþtýrýlýr,
// eðer eþit deðilse yorumun kapatýlmadýðý anlaþýlýp konsola hata yazdýrýlýr.

    if (yorumBasladi !=  yorumBitti) {
        printf("Lexical Analiz Hatasi. Kapatilmamis yorum.\n");
    }

    return 0;
}
