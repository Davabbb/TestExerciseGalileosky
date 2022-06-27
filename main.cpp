#include <iostream>
#include <vector>
#include <random>

struct Shop {
    int size;
    int favourite_soda = 0;
    std::vector<double> soda = {1, 1, 1, 1, 1};  // Допустим, что по умолчанию по одному ящику каждой газировки

    explicit Shop(int size) : size(size) {}
};

int Random() {
    std::random_device rand;
    std::mt19937 generator(rand());

    std::uniform_int_distribution<int> uniform_dist(0, 4);
    return uniform_dist(generator);
}

void Shop1(int day, int fav_soda, std::vector<Shop>& shops) {
    if (day == 0) {
        std::cout << "Магазин №1 заказывает " << 7 << " ящиков газировки №" << fav_soda << std::endl;
    } else if (day == 6) {
        for (int soda = 0; soda < 5; ++soda) {
            if (soda != fav_soda) {
                std::cout << "Магазин №1 заказывает " << 1.75 << " ящиков газировки №" << soda + 1 << std::endl;
            }
        }
    }
    if (day == 3) {
        shops[0].soda[fav_soda] += 7;
    } else if (day == 10) {
        for (int soda = 0; soda < 5; ++soda) {
            if (soda != fav_soda) {
                shops[0].soda[soda] += 1.75;
            }
        }
    }
}

void Solution(std::vector<Shop>& shops, int count_week_work) {
    int week = 7, count_week = 0;
    while (count_week_work != count_week) {

        int favourite_soda = 0;
        for (int i = 0; i < 5; ++i) {
            favourite_soda = Random();
            shops[i].favourite_soda = favourite_soda;
        }

        for (int day = 0; day < week * 2; ++day) {
            for (int shop = 0; shop < 5; ++shop) {
                favourite_soda = shops[shop].favourite_soda;
                shops[shop].soda[favourite_soda] -= 0.5;
                for (int soda = 0; soda < 4; soda++) {
                    if (soda != favourite_soda) {
                        shops[shop].soda[soda] -= 0.125;  // Буду считать, что любой вид остальной газировки всегда есть
                    }
                }
                
/*                std::cout << "day" << day + 1 + 7 * count_week << "_shop1 " << shops[0].soda[0] << " " << shops[0].soda[1]
                << " " << shops[0].soda[2] << " " << shops[0].soda[3] << " " <<  shops[0].soda[4] << std::endl;*/
            }
            Shop1(day, shops[0].favourite_soda, shops);
        }
        count_week += 2;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<Shop> shops;
    for (int i = 1; i < 6; ++i) {
        Shop a(i * 10);
        shops.push_back(a);
    }

    Solution(shops, 2);
    return 0;
}
