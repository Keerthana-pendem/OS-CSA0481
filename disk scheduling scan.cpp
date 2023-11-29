#include <stdio.h>
#include <stdlib.h>
void scan(int arr[], int head, int size, int disk_size) 
{
    int distance = 0;
    int seek_count = 0;
    int cur_track;
    int left = 0, right = 0;
    for (int i = 0; i < size; i++) 
	{
        for (int j = i + 1; j < size; j++) 
		{
            if (arr[i] > arr[j]) 
			{
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    for (int i = 0; i < size; i++) 
	{
        if (arr[i] > head) 
		{
            left = i - 1;
            right = i;
            break;
        }
    }
    printf("SCAN (Elevator) Disk Scheduling:\n");
    for (int i = right; i < size; i++) 
	{
        cur_track = arr[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }
    seek_count += (disk_size - head);
    for (int i = left; i >= 0; i--) 
	{
        cur_track = arr[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }
    printf("Total number of seek operations = %d\n", seek_count);
}
int main() 
{
    int size, head, disk_size;
    printf("Enter the size of request queue: ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the request queue elements:\n");
    for (int i = 0; i < size; i++) 
	{
        scanf("%d", &arr[i]);
    }
    printf("Enter the initial position of the head: ");
    scanf("%d", &head);
    printf("Enter the size of the disk: ");
    scanf("%d", &disk_size);
    scan(arr, head, size, disk_size);
    return 0;
}
