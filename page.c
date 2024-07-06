#include <stdio.h>
#include <stdlib.h>

int fault, p, k, flag;

void printframe(int frame[], int f) {
    int i;
    printf("Frames are\n");
    for (i = 0; i < f; i++) {
        printf("%d\t", frame[i]);
    }
    printf("\n");
}

void fcfs(int pages[], int n, int realframes[], int f) {
    int frames[f];
    int i, j;
    for (j = 0; j < f; j++) {
        frames[j] = realframes[j];
    }
    printf("Page Replacement\n");
    fault = 0;
    k = 0; // tracking next frame
    for (i = 0; i < n; i++) {
        p = pages[i];
        flag = 1;
        for (j = 0; j < f; j++) {
            if (p == frames[j]) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            fault++;
            frames[k] = p;
            k = (k + 1) % f;
        }
        printframe(frames, f);
    }
    printf("Total no of page faults: %d\n", fault);
}

void lru(int pages[], int n, int realframes[], int f) {
    int min; // to access least recent pages
    int frames[f], recent[f]; // last access page
    int i, j;

    for (j = 0; j < f; j++) {
        frames[j] = realframes[j];
        recent[j] = 0;
    }
    fault = 0;
    k = 1;
    for (i = 0; i < n; i++) {
        p = pages[i];
        flag = 1;
        for (j = 0; j < f; j++) {
            if (p == frames[j]) {
                flag = 0;
                recent[j] = k;
                k++;
                break;
            }
        }
        if (flag == 1) {
            fault++;
            min = 0;
            for (j = 0; j < f; j++) {
                if (recent[j] < recent[min]) {
                    min = j;
                }
            }
            frames[min] = p;
            recent[min] = k;
            k++;
        }
        printframe(frames, f);
    }
    printf("Total no of page faults: %d\n", fault);
}

void lfu(int pages[], int n, int realframes[], int f) {
    int frames[f], freq[f], min, i, j;
    for (j = 0; j < f; j++) {
        frames[j] = realframes[j];
        freq[j] = 0;
    }
    fault = 0;
    for (i = 0; i < n; i++) {
        p = pages[i];
        flag = 1;
        for (j = 0; j < f; j++) {
            if (p == frames[j]) {
                flag = 0;
                freq[j]++;
                break;
            }
        }
        if (flag == 1) {
            fault++;
            min = 0;
            for (j = 0; j < f; j++) {
                if (freq[j] < freq[min]) {
                    min = j;
                }
            }
            frames[min] = p;
            freq[min] = 1;
        }
        printframe(frames, f);
    }
    printf("Total no of page faults: %d\n", fault);
}

int main() {
    int n, pages[10], f, frames[10], i, j;
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("List the pages\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    printf("Enter the initial frames\n");
    for (i = 0; i < f; i++) {
        scanf("%d", &frames[i]);
    }

    printf("\nFCFS:\n");
    fcfs(pages, n, frames, f);

    printf("\nLRU:\n");
    lru(pages, n, frames, f);

    printf("\nLFU:\n");
    lfu(pages, n, frames, f);

    return 0;
}
