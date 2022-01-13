#include "FS.h"
#include "SD_MMC.h"
#define FILE_COLABORADORES "/COLABORADORES.txt"
#define FILE_USUARIOS "/USUARIOS.txt"
#define FILE_FECHAHORA "/FECHAHORA.txt"

String Id_Colaborador = "448895001";
String Fecha_Hora_Colaborador = "12";
String Fecha_Hora="";

String Dinero_Acumulado_String = "500";
String Total_Ingresos = "100";

String Id_Colaborador2 = "";
String Fecha_Hora_Colaborador2 = "";

String Dinero_Acumulado2 = "";
String Total_Ingresos2 = "";

int count;
String mensaje = "";

void setup(){
    Serial.begin(9600);
    if(!SD_MMC.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
//    writeFile(SD_MMC, "/Prueba1.txt",  PERSONAS+ "\n");   
//    sd_readFilePRUEBA1(SD_MMC, "/Prueba1.txt");   
//    readFile(SD_MMC, "/foo.txt");   

      sd_deleteARCHIVOS();
      sd_saveFileCOLABORADORES();
      sd_saveFileUSUARIO();
      
      sd_readFileCOLABORADORES(SD_MMC,FILE_COLABORADORES);
      sd_readFileUSUARIOS(SD_MMC,FILE_USUARIOS);
}

void sd_saveFileCOLABORADORES(){
    appendFile(SD_MMC, FILE_COLABORADORES, (Id_Colaborador + "\n"));
    appendFile(SD_MMC, FILE_COLABORADORES, (Fecha_Hora_Colaborador + "\n" ));

}

void sd_saveFileUSUARIO(){
    appendFile(SD_MMC, FILE_USUARIOS, (Dinero_Acumulado_String + "\n"));
    appendFile(SD_MMC, FILE_USUARIOS, (Total_Ingresos + "\n" ));
}

void sd_deleteARCHIVOS(){
    deleteFile(SD_MMC, FILE_USUARIOS);
    deleteFile(SD_MMC, FILE_COLABORADORES);
}

void sd_readFileCOLABORADORES(fs::FS &fs, const char * path){   
    
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file COLABORADORES: ");
    while(file.available()){
        char caracter = file.read();
        //String caracter2 = caracter;
        if(caracter != '\n'){
          mensaje.concat(caracter);
        }else{
          //Serial.print("funciona");
          //Serial.println(mensaje);
          count++;
          switch (count){
            case 1:
                Id_Colaborador2 = mensaje;
                Serial.println("Id_Colaborador: " + Id_Colaborador2);
            break;
            case 2:
                Fecha_Hora_Colaborador = mensaje;
                Serial.println("Year_Colaborador: " + Fecha_Hora_Colaborador2);
                count =0;
            break;
            }         
          mensaje = "";
        }
    }
  file.close();
}

void sd_readFileUSUARIOS(fs::FS &fs, const char * path){   
    
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file USUARIOS: ");
    while(file.available()){
        char caracter = file.read();
        //String caracter2 = caracter;
        if(caracter != '\n'){
          mensaje.concat(caracter);
        }else{
          //Serial.print("funciona");
          //Serial.println(mensaje);
          count++;
          switch (count){
            case 1:
                Dinero_Acumulado2 = mensaje;
                Serial.println("Dinero_Acumalado: " + Dinero_Acumulado2);
            break;
            case 2:
                Total_Ingresos2 = mensaje;
                Serial.println("Total_Ingresos: " + Total_Ingresos2);
                count =0;
            break;
            }         
          mensaje = "";
        }
    }
  file.close();
}

void sd_saveFECHAHORA(){
  deleteFile(SD_MMC, FILE_FECHAHORA);
  appendFile(SD_MMC, FILE_FECHAHORA, (Fecha_Hora + "\n"));
}
void loop(){

}

////////////////////////FUNCIONES////////////////////////////
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        char caracter = file.read();
        //String caracter2 = caracter;
        if(caracter != '\n'){
          mensaje.concat(caracter);
        }else{
          Serial.print("funciona");
          Serial.println(mensaje);
          mensaje = "";
        }
    }
}

void writeFile(fs::FS &fs, const char * path, String message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
}

void appendFile(fs::FS &fs, const char * path, String message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}
