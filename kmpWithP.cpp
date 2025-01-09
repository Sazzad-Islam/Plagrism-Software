///Group Name: ErroTax
///Group ID: 4
///Student ID-Name:
///19304025-Ashfaq Ahmed
///19304010-Christos Uster Biswas
///19104006-Mahadi Hassan
///19304030-Saif Ahmed
///19304017-Anas Afridi Arnab

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

void computeLPSArray(char* pat, int M, int* lps);

void KMPSearch(char* pat, char* txt, int* arr)
{
    int z = 0;
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            // store the occurrence of index
            arr[z++] = i-j;
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}

// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0) {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Driver program to test above function
int main()
{
    char data[1500];
    int z = 0; // length of the text file
    FILE* ptr;
    char ch;

    // Opening file in reading mode
    ptr = fopen("test.txt", "r");

    if (NULL == ptr) {
        cout<<"file can't be opened"<<endl;
    }

    // Storing in data array what is written in file
    // character by character using loop.
    do {
        ch = fgetc(ptr);
        data[z++] = ch;

        // Checking if character is not EOF(End of file).
        // If it is EOF stop reading.
    } while (ch != EOF);

    // Closing the file
    fclose(ptr);

    char txt[z];
    for(int i = 0; i<z; ++i)
    {
        txt[i] = data[i];
    }
    cout<<"Enter a pattern to search in text file:"<<endl;

    // taking input
    string input;
    cin>>input;

    // making pat char array from input
    char pat[input.length()];
    for(int i=0;i<input.length();++i)
    {
        pat[i] = input[i];
    }

    int txtL = z;
    int patL = input.length();
    int matchedL = 0;
    int spaceL = 1;
    int arr[100];
    fill_n(arr, 100, -1);

    // make kmpSearch
    KMPSearch(pat, txt, arr);

    // calculate total matched character
    for(int i = 0; i < 100; ++i)
    {
        if(arr[i] == -1)
            break;
        matchedL += patL;
    }

    for(int i=0; i<txtL; ++i)
    {
        if(txt[i]==' ')
        {
            spaceL++;
        }
    }

    //Calculate the percentage of matching
    float result = ((matchedL+0.0)/txtL)*100;

    cout<<endl;
    cout<<"============Result============"<<endl;
    cout<<"Total character: "<<txtL<<endl;
    cout<<"Total occurrence: "<<matchedL/patL<<" times"<<endl;
    cout<<"Total words: "<<spaceL<<endl<<endl;
    cout<<"Matched percentage: "<<result<<"%"<<endl;
    cout<<"=============================="<<endl;
    return 0;
}
