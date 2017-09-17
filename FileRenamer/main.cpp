#include <QDirIterator>
#include <QDebug>
#include <QImageReader>

int main(int argc, char *argv[])
{

    QString picPath = "F:/test/";
    QDir dir(picPath);

//    QStringList filters("*.mp3");
//    QFileInfoList list = dir.entryInfoList(filters);

    //windows桌面自动更换的壁纸存储地址如下
//C:\Users\TEM_DEV\AppData\Local\Packages\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\LocalState\Assets

    int index = 1;

    QFileInfoList list = dir.entryInfoList();
    for(int i = 0; i< list.size();i++)
    {
        QFileInfo fileInfo = list.at(i);
        fileInfo.isDir();
        if(!fileInfo.isDir()&&fileInfo.suffix().isEmpty())
        {
            QString fileOriginalPath = fileInfo.absoluteFilePath();//with the file name

            bool imageFlag = false;
            QString imageSuffix;
            {
                QImageReader reader(fileOriginalPath);//after that the reader lock the file, so the brace is necessary
                imageSuffix = reader.format();
                //imageFlag = reader.format()=="png"||reader.format()=="jpeg"||reader.format() == "gif";
                imageFlag = reader.format() == "jpeg";
            }

            if(imageFlag)
            {                
                QString fileNewPath = fileInfo.absolutePath()+"/pic_"+QString::number(index)+"."+imageSuffix;
                bool flag = dir.rename(fileOriginalPath,fileNewPath);
                if(flag)
                {
                    qDebug()<<fileInfo.baseName()<<" convert to pic "<< QString::number(index);
                    index++;
                }
                else
                    qDebug()<<fileOriginalPath<<" fail to convert";
            }
        }
    }
    qDebug()<<"rename total "<<QString::number(--index)<<" files";
    return 0;
}
