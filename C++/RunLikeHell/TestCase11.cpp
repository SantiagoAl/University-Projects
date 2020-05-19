// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase11.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] {512, 98, 619, 512, 86, 866, 23, 446, 241, 630,
        539, 405, 91, 150, 922, 19, 500, 663, 960, 673, 665, 924, 345,
        733, 833, 226, 952, 522, 959, 563, 472, 955, 977, 626, 791,
        422, 618, 604, 458, 580, 184, 140, 610, 23, 609, 838, 645, 398,
        544, 148, 533, 28, 387, 276, 45, 497, 165, 286, 535, 489, 912,
        201, 899, 575, 872, 717, 769, 606, 136, 370, 395, 647, 392,
        928, 324, 398, 344, 668, 95, 300, 680, 551, 564, 417, 357, 469,
        399, 48, 398, 74, 852, 55, 590, 65, 180, 75, 529, 193, 808,
        290, 896, 697, 493, 457, 652, 623, 9, 902, 434, 460, 425, 678,
        507, 834, 56, 896, 86, 201, 188, 736, 585, 593, 298, 623, 148,
        748, 488, 609, 106, 43, 570, 144, 247, 666, 259, 459, 854, 177,
        122, 480, 821, 860, 460, 102, 910, 726, 16, 474, 964, 284, 204,
        494, 849, 75, 103, 40, 284, 978, 630, 513, 459, 696, 677, 592,
        807, 290, 179, 513, 905, 300, 677, 439, 865, 57, 549, 844, 381,
        695, 473, 542, 975, 996, 644, 304, 550, 902, 303, 669, 803,
        577, 21, 145, 454, 37, 199, 850, 819, 43, 444, 112};
    int ans = 58219;

    int size = sizeof(blocks) / sizeof(blocks[0]);

    RunLikeHell hell {};

    if (hell.maxGain(blocks, size) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}