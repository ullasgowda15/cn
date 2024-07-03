#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int generate_random_time(int max) {
    int random_time;
    random_time = rand() % 10;
    random_time = random_time % max;
    if (random_time == 0)
        random_time = 1;
    return random_time;
}

int main() {
    int i, j, time, packets[5], output_rate, input_rate, bucket_size, packets_remaining;
    int packet_size, remaining_packet_size = 0, arrival_time, flag = 0;
    printf("Enter 5 packets in the stream:");
    for (i = 0; i < 5; ++i) {
        scanf("%d", &packets[i]);
    }
    printf("\nEnter the Output Rate:");
    scanf("%d", &output_rate);
    printf("\nEnter the Bucket Size:");
    scanf("%d", &bucket_size);
    for (i = 0; i < 5; ++i) {
        if ((packets[i] + remaining_packet_size) > bucket_size) {
            if (packets[i] > bucket_size)
                printf("\n\n Incoming packet size (%d) is GREATER than bucket capacity - !!!REJECTED!!!", packets[i]);
            else
                printf("\nBucket capacity exceeded - !!!REJECTED!!!");
        } else {
            for (j = 0;; ++j) {
                packets_remaining = 4 - i;
                packet_size = packets[i];
                remaining_packet_size += packet_size;
                printf("\n\n Incoming Packet Size: %d", packet_size);
                printf("\n Transmission Left: %d", remaining_packet_size);
                arrival_time = generate_random_time(5) * 2;
                printf("\n\n Next Packet will come at: %d", arrival_time);
                for (time = 0; time < arrival_time; time += 1) {
                    printf("\n Time left: %d", time);
                    sleep(1);
                    if (remaining_packet_size){
                        printf(" - !!!Transmitted!!!");
                        if (remaining_packet_size <= output_rate)
                            remaining_packet_size = 0;
                        else
                            remaining_packet_size -= output_rate;
                        printf(" - Bytes Remaining: %d", remaining_packet_size);
                    } else {
                        printf(" - No Packets to transmit!!!");
                    }
                }
                if (remaining_packet_size != 0)
                    flag = 1;
                break;
            }
        }
    }
}

/*
Enter 5 packets in the stream: 8 15 6 12 10

Enter the Output Rate: 5

Enter the Bucket Size: 20


 Incoming Packet Size: 8
 Transmission Left: 8

 Next Packet will come at: 4

 Time left: 0 - !!!Transmitted!!! - Bytes Remaining: 3
 Time left: 1 - !!!Transmitted!!! - Bytes Remaining: 0
 Time left: 2 - No Packets to transmit!!!
 Time left: 3 - No Packets to transmit!!!

 Incoming packet size (15) is GREATER than bucket capacity - !!!REJECTED!!!

 Incoming Packet Size: 6
 Transmission Left: 6

 Next Packet will come at: 2

 Time left: 0 - !!!Transmitted!!! - Bytes Remaining: 1
 Time left: 1 - !!!Transmitted!!! - Bytes Remaining: 0

 Incoming Packet Size: 12
 Transmission Left: 12

 Next Packet will come at: 8

 Time left: 0 - !!!Transmitted!!! - Bytes Remaining: 7
 Time left: 1 - !!!Transmitted!!! - Bytes Remaining: 2
 Time left: 2 - !!!Transmitted!!! - Bytes Remaining: 0
 Time left: 3 - No Packets to transmit!!!
 Time left: 4 - No Packets to transmit!!!
 Time left: 5 - No Packets to transmit!!!
 Time left: 6 - No Packets to transmit!!!
 Time left: 7 - No Packets to transmit!!!

 Incoming Packet Size: 10
 Transmission Left: 10

 Next Packet will come at: 10

 Time left: 0 - !!!Transmitted!!! - Bytes Remaining: 5
 Time left: 1 - !!!Transmitted!!! - Bytes Remaining: 0
 Time left: 2 - No Packets to transmit!!!
 Time left: 3 - No Packets to transmit!!!
 Time left: 4 - No Packets to transmit!!!
 Time left: 5 - No Packets to transmit!!!
 Time left: 6 - No Packets to transmit!!!
 Time left: 7 - No Packets to transmit!!!
 Time left: 8 - No Packets to transmit!!!
 Time left: 9 - No Packets to transmit!!!

*/