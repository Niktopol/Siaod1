#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
void coutp(unsigned int x){
    int n = sizeof(int)*8;
    unsigned mask = (1<<(n-1));
    for(int i = 0; i < n; i++){
        std::cout << ((x&mask)>>(n-i-1));
        mask = mask >> 1;
    }
    std::cout << std::endl;
}
void genFile(int size){
    std::vector<int> nums(size);
    for (int i = 0; i < size; i++){
        nums.at(i) = i;
    }
    std::shuffle(std::begin(nums), std::end(nums), std::default_random_engine());
    std::ofstream fout("input.txt");
    if (fout.is_open()){
        for (int i : nums){
            fout << i << std::endl;
        }    
    }
    
}
int main(){
    
    unsigned int a = 0xBFC;

    coutp(a);
    a = (a|((1<<(17))|(1<<(15))));

    coutp(a);

    a = a & ~(7 << 3);
    coutp(a);

    std::cout << "Enter a number: " << std::endl;
    std::cin >> a;
    coutp(a);
    a = a << 6;
    coutp(a);
    std::cout << a << std::endl;

    std::cout << "Enter a number: " << std::endl;
    std::cin >> a;
    coutp(a);
    a = a >> 6;
    coutp(a);
    std::cout << a << std::endl;

    unsigned mask = (1<<(sizeof(int)*8-1));
    std::cout << "Enter a number: " << std::endl;
    std::cin >> a;
    coutp(a);
    unsigned int bit;
    std::cout << "Enter bit number: " << std::endl;
    std::cin >> bit;
    mask = ~(mask >> (31 - bit));
    a = a & mask;
    coutp(a);

    std::cout << "Enter array size [0-8]: " << std::endl;
    std::cin >> a;
    unsigned int *arr = new unsigned int[a];
    std::cout << "Enter elements: " << std::endl;
    for (int i = 0; i < a; i++){
        std::cin >> arr[i];
    }
    unsigned char sorter = 0;
    for (int i = 0; i < a; i++){
        sorter = sorter | ((1 << 7) >> arr[i]);
    }
    int ind = 0;
    for (int i = 0; i < sizeof(char)*8; i++){
        if (sorter & ((1 << 7) >> i)){
            arr[ind] = i;
            ind++;
        }
    }
    for (int i = 0; i < a; i++){
        std::cout << arr[i] << " ";
    }
    
    std::cout << std::endl;

    std::cout << "Enter array size [0-64]: " << std::endl;
    std::cin >> a;
    unsigned int *nextArr = new unsigned int[a];
    std::cout << "Enter elements: " << std::endl;
    for (int i = 0; i < a; i++){
        std::cin >> nextArr[i];
    }
    unsigned char bigSorter[] = {0,0,0,0,0,0,0,0};
    for (int i = 0; i < a; i++){
        bigSorter[int(nextArr[i]/8)] = bigSorter[int(nextArr[i]/8)] | ((1 << 7) >> nextArr[i]%8);
    }
    ind = 0;
    for (int i = 0; i < sizeof(char)*8; i++){
        for (int j = 0; j < sizeof(char)*8; j++){
            if (bigSorter[i] & ((1 << 7) >> j)){
                nextArr[ind] = 8*i+j;
                ind++;
            }
        }
    }
    for (int i = 0; i < a; i++){
        std::cout << nextArr[i] << " ";
    }
    std::cout << std::endl;
    
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    std::string line;
    std::cout << "Enter amount of numbers [0-10000000]: " << std::endl;
    std::cin >> a;
    genFile(a);
    std::vector<unsigned char> fileSorter(int(a/8)+1);
    while(std::getline(fin, line)){
        fileSorter.at(int(std::stoi(line)/8)) = fileSorter.at(int(std::stoi(line)/8)) | ((1 << 7) >> std::stoi(line)%8);
    }
    ind = 0;
    for (int i = 0; i < fileSorter.size(); i++){
        for (int j = 0; j < sizeof(char)*8; j++){
            if (fileSorter.at(i) & ((1 << 7) >> j)){
                fout << 8*i+j << std::endl;
                ind++;
            }
        }
    }
    delete[] arr;
    delete[] nextArr;
    return 0;
}