// Program for error detection code using CRC

#include <stdio.h>

int main() {
    int i, j, k = 0, flag=1, n, m;
    int frame[16], generator[16], remainder[20], quotient[16];

    printf("Enter the degree of generator : ");
    scanf("%d", &n);

    printf("Enter the generator : ");
    for(i=0; i<=n; i++) {
        scanf("%d", &generator[i]);
    }

    printf("Enter the degree of frames : ");
    scanf("%d", &m);

    printf("Enter the frame : ");
    for(i=0; i<=m; i++) {
        scanf("%d", &frame[i]);
    }

    if(m<n || (generator[0] && generator[n])==0) {
        printf("Not a proper generator.");
    }

    for(i=m+1; i<=m+n; i++) {
        frame[i] = 0;
    }
    for(j=0; j<=n; j++) {
        remainder[j] = frame[j];
    }
    for(i=n; i<=m+n; i++) {
        if(i>n) {
            for (j=0; j<n; j++) {
                remainder[j] = remainder[j + 1];
            }
            remainder[j] = frame[i];
        }
        if(remainder[0]) {
            quotient[k++] = 1;
        } else {
            quotient[k++] = 0;
            continue;
        }
        for(j=0; j<=n; j++) {
            remainder[j] = remainder[j] ^ generator[j];
        }
    }

    printf("Quotient is : ");
    for(j=0; j<k; j++) {
        printf("%d ", quotient[j]);
    }

    printf("\nRemainder is : ");
    for(i=1; i<=n; i++) {
        printf("%d ", remainder[i]);
    }

    printf("\nTransmitted frame is : ");
    for(i=m+1, j=1; i<=m+n; i++, j++) {
        frame[i] = remainder[j];
    }
    for(i=0; i<=m+n; i++) {
        printf("%d ", frame[i]);
    }

    printf("\nEnter the degree of frame : ");
    scanf("%d", &m);
    printf("Enter the frame : ");
    for(i=0; i<=m; i++) {
        scanf("%d", &frame[i]);
    }

    for(j=0; j<=n; j++) {
        remainder[j] = frame[j];
    }
    k = 0;
    for(i=n; i<=m; i++) {
        if(i>n) {
            for(j=0; j<n; j++) {
                remainder[j] = remainder[j + 1];
            }
            remainder[j] = frame[i];
        }

        if(remainder[0]) {
            quotient[k++] = 1;
        } else {
            quotient[k++] = 0;
            continue;
        }

        for(j=0; j<=n; j++) {
            remainder[j] = remainder[j] ^ generator[j];
        }
    }

    printf("Quotient is : ");
    for(j=0; j<k; j++) {
        printf("%d ", quotient[j]);
    }

    printf("\nRemainder is : ");
    for(i=1; i<=n; i++) {
        printf("%d ", remainder[i]);
    }

    for(i=1; i<=n; i++) {
        if (remainder[i]) {
            flag = 0;
        }
    }
    if(flag) {
        printf("\nNo Error");
    } else {
        printf("\nError");
    }
}

