#include "SM630.h"


//need to give output buffer


unsigned char calc_checksum (unsigned char *);
int check_sum (unsigned char *);
int recv_check(unsigned char *);
int command_check(unsigned char *);
int retreive_addr(unsigned char *);
int __serial_gets();
void __serial_puts(unsigned char *,int);
void signal_handler_IO (int);
extern int match_fingerprint_id (unsigned short , unsigned short);
extern int serial_init();
extern int add_fingerprint(unsigned short);
extern int search_fingerprint_id(unsigned short);
extern int empty_db();

extern int empty_db(){
    int status = 0;
    bytes_expected = 7;

    unsigned char length = 0x01;
    unsigned char command[8];

    command[0] = PKT_HEAD_1;
    command[1] = PKT_HEAD_2;
    command[2] = COMMAND_PKT;
    command[3] = length;
    command[4] = EMPTY_DATABASE;
    command[5] = calc_checksum(command);

    __serial_puts(command,6);

    int bytes=0;

    bytes_expected = 6;
    bytes +=__serial_gets();
    status += recv_check(rec);

    if (status)
            return status;

    bytes_expected = 7;
    bytes += __serial_gets();
    status += command_check(rec);

    return status;
}

extern int add_fingerprint (unsigned short addr) {
        unsigned char adr[2];
        int status = 0;
        adr[0] = (unsigned char) ((short) 0xff & addr);
        addr &= (short)0xff00;
        addr = addr >> 8;
        adr[1] = (unsigned char) addr;

        unsigned char length = 0x03;
        unsigned char command[8];
        command[0] = PKT_HEAD_1;
        command[1] = PKT_HEAD_2;
        command[2] = COMMAND_PKT;
        command[3] = length;
        command[4] = ADD_FINGERPRINT;
        command[5] = adr[1];
        command[6] = adr[0];
        command[7] = calc_checksum(command);

        //int j;
        //for (j=0 ; j < 8; j++)
        //printf("%x ",command[j]);

        __serial_puts(command,8);

        int bytes=0;

        bytes_expected = 6;
        bytes +=__serial_gets();
        status += recv_check(rec);

        if (status)
            return status;

        printf("\nbytes = %d\n",bytes);

        bytes_expected = 7;
        bytes+=__serial_gets();
        status += command_check(rec);

        if (status)
            return status;


        printf("\nbytes = %d\n",bytes);

        bytes_expected = 7;
        bytes+= __serial_gets();
        status += command_check(rec);


        printf("\nbytes = %d\n",bytes);

        return status;
}

int search_fingerprint_id (unsigned short addr) {

        unsigned char adr[2];
        int status = 0;
        adr[0] = (unsigned char) ((short) 0xff & addr);
        addr &= (short)0xff00;
        addr = addr >> 8;
        adr[1] = (unsigned char) addr;

        unsigned char length = 0x03;
        unsigned char command[8];
        command[0] = PKT_HEAD_1;
        command[1] = PKT_HEAD_2;
        command[2] = COMMAND_PKT;
        command[3] = length;
        command[4] = SEARCH_DATABASE;
        command[5] = adr[1];
        command[6] = adr[0];
        command[7] = calc_checksum(command);

        //int j;
        //for (j=0 ; j < 8; j++)
        //printf("%x ",command[j]);

        __serial_puts(command,8);

        int bytes=0;

        bytes_expected = 13;
        bytes +=__serial_gets();
        status += recv_check(rec);
        status += command_check(rec+6);

        printf("\nbytes = %d\n",bytes);

        return status;
}







extern int match_fingerprint_id (unsigned short start_addr, unsigned short range) {

        unsigned char start_adr[2];
        unsigned char range_val[2];

        int status = 0;
        start_adr[0] = (unsigned char) ((short) 0xff & start_addr);
        start_addr &= (short)0xff00;
        start_addr = start_addr >> 8;
        start_adr[1] = (unsigned char) start_addr;

        range_val[0] = (unsigned char) ((short) 0xff & range);
        range &= (short)0xff00;
        range = range >> 8;
        range_val[1] = (unsigned char) range;

        unsigned char length = 0x05;
        unsigned char command[8];
        command[0] = PKT_HEAD_1;
        command[1] = PKT_HEAD_2;
        command[2] = COMMAND_PKT;
        command[3] = length;
        command[4] = SEARCH_FINGERPRINT;
        command[5] = start_adr[1];
        command[6] = start_adr[0];
        command[7] = range_val[1];
        command[8] = range_val[0];
        command[9] = calc_checksum(command);

        //int j;
        //for (j=0 ; j < 8; j++)
        //printf("%x ",command[j]);

        __serial_puts(command,10);

        int bytes=0;


        bytes_expected = 6;
        bytes +=__serial_gets();

        if (bytes == 13){
        status += recv_check(rec);
        status += command_check(rec + 6);
        return status;
        }

        if (status)
            return (-status);

        bytes_expected = 7;
        bytes += __serial_gets();


        status += command_check(rec);

        if (status)
            return (-status);


        bytes_expected = 7;
        bytes += __serial_gets();


        return ((-status) + retreive_addr(rec));



}

int retreive_addr(unsigned char *rec_buf) {

        int addr = 0;

        if (check_sum(rec_buf))
                return -1;
        if (rec_buf[3] == 0x02 && rec_buf[5] == FINGER_NOT_FOUND)
                return -2;

        printf("\n %x %x\n",rec[6],rec[7]);

        addr  = rec_buf[6];
        addr = addr << 8;
        addr = addr | rec_buf[7];

        return addr;
}




int command_check(unsigned char *rec_buf) {


        if (check_sum(rec_buf))
                return 1;

        switch(rec_buf[5]) {

                case OP_SUCCESS:
                        printf("\nOperation Successful!!!\n");
                        return 0;

                case FINGER_FALIURE:
                        printf("\nFinger Swipe Faliure\n");
                        return 1;

                case TIME_OUT:
                        printf("\nOperation Timed Out\n");
                        return 1;

                case PARAM_ERROR:
                        printf("\nParameter Error\n");
                        return 1;

                case FINGER_MATCH_ID:
                        printf("\nFingerPrint present at the requested ID\n");
                        return 0;

                case NO_FINGER_MATCH_ID:
                        printf("\nFingerPrints not present at the given ID\n");
                        return 1;

                case FINGER_NOT_FOUND:
                        printf("\nFingerPrint Not in Given Range\n");
                        return 1;

        }
}


int read_logo(unsigned char *a) {

        int logo_length = 24;
        int bytes = 36;
        unsigned char length = 0x01;

        //SET MINIMUM BYTES TO BE RECEIVED

        bytes_expected = bytes;

        printf("Bytes_expected = %d\n", bytes_expected);

        unsigned char command[6];
        command[0] = PKT_HEAD_1;
        command[1] = PKT_HEAD_2;
        command[2] = COMMAND_PKT;
        command[3] = length;
        command[4] = READ_LOGO;
        command[5] = calc_checksum(command);

        __serial_puts(command,6);

        __serial_gets();

        int status = recv_check(rec);


        printf("\nThe receive check status  %d \n", status);

        if (status)
                return 1;

        if(check_sum(rec+6))
                return 1;

        int i,j=0;

        for (i = 11 ; i<= logo_length + 10; i++)

        {
                a[j] = rec[i];
                j++;
        }



        return 0;

}



//check first six bytes of the receive buffer to be the receive correct packet and return status

//error codes for the response of the function
//recieve error 1
//unknown error 2
//checksum error

int recv_check(unsigned char *rec_buf) {

        if(!check_sum(rec_buf)) {

                if (rec[4] == RECV_CORRECT)
                        return 0;

                if( rec[4] == RECV_ERROR )

                              return 1;
                else
                        return 2;
                }

        else
                return 3;

}




//checksum from the initial to the final position in the buffer


int check_sum(unsigned char *rec_buf) {

        int i,length;
        length =  rec_buf[3];
        length += 3;
        int  sum = 0x00;
        unsigned char charsum;

        for (i=0; i <= length ; i++)
        sum += rec_buf[i];

        charsum = (unsigned char) sum;

        if (charsum == rec_buf[i])
                return 0;
        else
                printf("CheckSum error\n");
                return 1;
}


unsigned char calc_checksum(unsigned char *commd) {

        int sum,j;
        sum = 0x00;
        int length = commd[3];
        length += 3 ;
        int i;


        for (i=0; i <= length; i++)
          sum += commd[i];

       // printf("\n%x the value of checksum\n",sum);


        return sum;

}

void __serial_puts(unsigned char *a, int count) {

        write(fd,a,count);
}

//bytes_received is the number of bytes

int __serial_gets() {

int i,n=0;
int offset=0;
        printf("Hello\n");
        while(bytes_expected > 0){


        if (!wait_flag)
                {
                        n=read(fd,rec+offset,300);
                        for(i=offset;i<offset+n;i++)
                        printf("%x ",rec[i]);
                        bytes_expected-=n;
                        offset+=n;
                        wait_flag = TRUE;


                }

//offset + 1 is the number of bytes read

}
return offset;
}


int serial_init() {


// Testing the output terminal

        int status = 0;

        output=fopen("/dev/tty", "w");

        if(!output) {
                fprintf(stderr, "Unable to open /dev/tty\n");
                status+=1;
        }

        fputs("Haanji\n",output);





//BAUD RATE OF 57600, 8-bit data, 1 Stop bit and No Parity

        BAUD = B57600;
        DATABITS = CS8;
        STOPBITS = 0;
        PARITYON = 0;
        PARITY = 0;

//open the serial port in non-blocking mode

        fd = open(devicename, O_RDWR | O_NOCTTY | O_NONBLOCK);

         if (fd < 0)
      {
         perror(devicename);
         status += 1;
      }



      saio.sa_handler = signal_handler_IO;
      sigemptyset(&saio.sa_mask);   //saio.sa_mask = 0;
      saio.sa_flags = 0;
      saio.sa_restorer = NULL;
      sigaction(SIGIO,&saio,NULL);

                                                                        // allow the process to receive SIGIO
      fcntl(fd, F_SETOWN, getpid());                                    // Make the process receive SIGURG

      fcntl(fd, F_SETFL, FASYNC);                                       //Set the Asynchronous Flag

      tcgetattr(fd,&oldtio); // save current port settings
                                                                        // set new port settings for canonical input processing
      newtio.c_cflag = BAUD | DATABITS | STOPBITS | PARITYON | PARITY | CLOCAL | CREAD;
      newtio.c_iflag = IGNPAR;
      newtio.c_oflag = 0;
      newtio.c_lflag = 0;                                               //ICANON;
      newtio.c_cc[VMIN]=1;
      newtio.c_cc[VTIME]=0;
      tcflush(fd, TCIFLUSH);
      tcsetattr(fd,TCSANOW,&newtio);

      return status;

}

void signal_handler_IO (int val) {

        printf("byte recevied ctd next line \n");
        wait_flag = FALSE;
}
