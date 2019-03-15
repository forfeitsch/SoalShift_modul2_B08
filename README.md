# SoalShift_modul2_B08

1. Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
   - Catatan : Tidak boleh menggunakan crontab.
*Observasi*
   Membuat script dengan c, untuk melakukan pemindahan dan perubahan nama file.
*Penjelasan*
   Melakukan pembacaan pada file ber-ekstensi "*.png*" serta membuat fullpath untuk folder asal dan tujuannya.
```
char p_old[100]="/home/schielen/modul2/gambar/";
char p_new[100]="/home/schielen/modul2/";

```
   Dikarenakan kami tidak menggunakan *chdir/opendir*dalam membaca folder asal dan folder tujuan, tapi kami menggunakan *opendir* untuk membaca folder yang berisi gambar yang nantinya akan diubah.

```
if ((dir = opendir ("/home/schielen/modul2/gambar/")) != NULL)

```   

   lalu membuat loop, dengan kondisi ``` while ((ent = readdir (dir)) != NULL) ```, kemudian untuk melakukan pengerjaannya, kami menggunakan fungsi *string*, dimana ia akan membaca selama file tersebut *png* maka akan dilakukan penyelesaian seperti ini :
```
str = strstr(ent->d_name,".png"); //mencari file png
        if(str) {
          strcpy(temp,p_old); 
          strcat(temp,ent->d_name);
          strcpy(oldname,temp);
          name = strtok(ent->d_name,".");
          strcat(name, add);
          strcpy(temp,p_new);
          strcat(temp,name);
          strcpy(newname,temp);
          printf("%s\n", newname);
          printf("%s\n", oldname);
          rename(oldname,newname);
        }

```
   
2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
   - Catatan: Tidak boleh menggunakan crontab
*Penjelasan*
- Buat folder "hatiku", lalu buat file "elen.ku"
  ```
  mkdir hatiku
  cd hatiku
  touch elen.ku
  ```
- Kemudian buat file soal2.c menggunakan ```nano soal2.c``` dengan isinya seperti yang ada dalam.

- Dapatkan owner dan grup dari "elen.ku"
    ```
    struct stat st;
    char folder[20] = "hatiku/elen.ku";
    stat(folder, &st);
    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);
    ```
  - Pastikan owner dan grupnya adalah "www-data", baru filenya dihapus
    ```
    char nama[10] = "www-data";
    int usr = strcmp(pw->pw_name, nama);
    int grp = strcmp(gr->gr_name, nama);
    if(usr == 0 && grp == 0)
      remove(folder);
    ```
  - Lakukan setiap 3 detik
    ```
    sleep(3);
    ```
- Ubah permission file "elen.ku" menjadi 777
  ```
  chmod 777 elen.ku
  ```
- Lalu atur nama owner dan grup pada file "elen.ku" menjadi "www-data"
  ```
  sudo chown www-data:www-data elen.ku
  ```
- Compile file "soal2.c" lalu execute
  ```
  gcc -o soal2 soal2.c
  ./soal2
  ```
- File "elen.ku" terhapus


3. Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
   1. mengekstrak file zip tersebut.
   2. menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
   - Catatan:  
     * Gunakan fork dan exec.
     * Gunakan minimal 3 proses yang diakhiri dengan exec.
     * Gunakan pipe
     * Pastikan file daftar.txt dapat diakses dari text editor

*Penjelasan*
   Melakukan *unzipping* file dengan *exec*
   ``` 
   
   char *argv[] = {"unzip", "/home/schielen/modul2/campur2.zip", NULL};
   execv("/usr/bin/unzip", argv);
    
   ```
   
   Membuat *fork()* untuk melakukan *exec* dan *pipe*

```


    char *argv[] = {"ls", "/home/schielen/modul2/campur2", NULL};
    dup2(pipes[1],1);
    close(pipes[0]);
    close(pipes[2]);
    close(pipes[3]);


    execv("/bin/ls", argv);


    } else
        {
          pid_t child_id2;
          child_id2 = fork();
            if (child_id2 == 0) {
        // this is child
        while ((wait(&status2)) > 0);
        char *argv[] = {"grep", ".txt$", NULL};
        dup2(pipes[0],0);
        close(pipes[1]);
        close(pipes[2]);
        dup2(pipes[3],1);
        execv("/bin/grep", argv);

        }
        else
        {
          
          FILE *file = fopen("/home/schielen/modul2/daftar.txt", "w+");
          close(pipes[0]);
          close(pipes[1]);
          close(pipes[3]);
          char str[10000];
          read(pipes[2],str,sizeof(str));
          fputs(str,file);

```

   Disini kami menggunakan *twopipes.c* dimana kita bisa menggunakan dua *pipes* sekaligus yang kami butuhkan untuk ``` char *argv[] = {"grep", ".txt$", NULL}; ``` dan untuk membuka file ```  FILE *file = fopen("/home/schielen/modul2/daftar.txt", "w+"); ```

**Referensi**
   - http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html

4. Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.
   - Contoh:
     - File makan_enak.txt terakhir dibuka pada detik ke-1
     - Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt
   - Catatan: 
     - Dilarang menggunakan crontab
     - Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst
     
*Penyelesaian*
   Melakukan *opendir* ke ```  if ((dir = opendir ("/home/schielen/Documents/makanan/")) != NULL) ```
  Lalu kita akan mengecek selama kita berada dalam direktori tersebut :
```
         char str[100] = "/makan_enak.txt";
         time_t acc; // access time
         time_t ccc; // local time
         time(&ccc);
         struct tm *info;
         acc = a_time("/home/schielen/Documents/makanan/makan_enak.txt");
         info = localtime(&acc);
        
  ```
   Kemudian untuk melakukan pengecekan kita menggunakan diff time, untuk membandingkan antara waktu sekarang dengan waktu akses time, digunakan untuk pembacaan waktu 30 detik dan juga untuk melakukan pembuatan file setiap kita mengakses file *makanan_enak.txt* :
  ```
            if(difftime(ccc, acc)<=30){
            FILE *file;
            char tmp[100];
            
            sprintf(tmp,"/home/schielen/Documents/makanan/makan_sehat%d.txt",i);
            file = fopen(tmp,"w+");

```
jangan lupa diakhir berikan ``` sleep(5) ``` karena pembacaan tersebut selama selang waktu 5 detik.
   
5. Kerjakan poin i dan ii di bawah:
   1. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
     - Ket:
       - Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
       - Per menit memasukkan log#.log ke dalam folder tersebut
       - ‘#’ : increment per menit. Mulai dari 1
   2. Buatlah program c untuk menghentikan program di atas.
> NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

*Penyelesaian*

Untuk mengerjakan ini, kita menggunakan daemon lalu, kita menggunakan nama folder dengan fungsi time.h lalu disini kita menggunakan count. 

Dimana count yang dimod 30 itu sema dengan 0, maka file akan membuat folder baru. Setelah itu program akan membuat file dan mengkopi dari log. Lalu akan menjadi seperti ini :

```
while(1) {
        time_t t2 = time(0) ; //buat nama folder yang dengan menangkap timestamp ketika kode ini dieksekusi
        struct tm *tmp;
        char line[80];
        tmp = localtime(&t2);
        strftime(line, sizeof(line), "%d:%m:%Y-%H-%M", tmp);
        char path[100], t[100];
        if(count % 30 == 1){ //if digunakan untuk membuat folder
            strcpy(t, line);
            strcpy(path, "/home/schielen/log/");
            strcat(path, t);
            strcat(path, "/");
            mkdir(path, 0777);
        }
        //yang inidigunakan untuk membuat file
        char str[10];
        strcpy(str, "");
        sprintf(str, "log%d", count);
        strcat(str, ".log");
        char strfinal[100];
        strcpy(strfinal, path);
        strcat(strfinal,str);
        // rename("/var/log/syslog", path);
        // ini untuk membuat file log1.log dan selanjutnya
        FILE *fc, *fs;
        int c;
        fc = fopen("/var/log/syslog", "r");
        fs = fopen(strfinal, "w");
        while(1) {
            c = fgetc(fc);
            if(feof(fc)) break;
            fputc(c, fs);
        }
        fclose(fc);
        fclose(fs);
        sleep(60);
        count++; //count ini sangat berguna di if
    }
    exit(EXIT_SUCCESS);
}
```

Sekian laporan dari kami dan Terimakasih.
