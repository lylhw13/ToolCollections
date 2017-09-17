#include <QCoreApplication>
#include <QFileInfoList>
#include <QDir>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QString dirPath("E:/count/");
    QStringList filters;
    filters<<"*.cpp"<<"*.h";
    bool countMiddleBlankLines = true;
    bool countTailBlankLines = false;

    int totalLines = 0;
    int filesNumber = 0;

    QDir dir(dirPath);
    QFileInfoList list = dir.entryInfoList(filters);

    qDebug()<< "Count Condition : ";
    qDebug()<< (countMiddleBlankLines?"Count ":"Donot count ")<<"the middle blank lines.";
    qDebug()<< (countTailBlankLines?"Count ":"Donot count ")<<"the tail blank lines.\n";

    for(int i = 0; i<list.count();i++)
    {
        QFileInfo fileInfo = list.at(i);

        if(fileInfo.baseName().isEmpty())
            continue;

        QFile file(fileInfo.canonicalFilePath());
        if(!file.open(QFile::ReadOnly))
        {
            qDebug()<<"Unable to open " <<fileInfo.fileName();
            continue;
        }
        QTextStream out(&file);

        int fileLines = 0;
        int blankLines = 0;

        while(!out.atEnd())
        {
            QString line = out.readLine();
            if(line.isEmpty())
            {
                blankLines++;
            }
            else
            {
                fileLines++;

                if(countMiddleBlankLines)
                    fileLines += blankLines;//it is the middleline.

                blankLines = 0;
            }
        }
        if(countTailBlankLines)
            fileLines += blankLines;

        qDebug()<<(++filesNumber)<<" "<<fileInfo.fileName() << " has total lines "<<fileLines;

        totalLines += fileLines;
        file.close();
    }

    qDebug()<<"Total files number "<< filesNumber;
    qDebug()<<"Total lines "<<totalLines;
}
