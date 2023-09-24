#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

class SingletonDataBase;

class SingletonDataBaseDestroyer
{
private:
    SingletonDataBase * p_instance; /**< Pointer to SingletonDataBase instance */
public:
    ~SingletonDataBaseDestroyer() {
        delete p_instance;
        qDebug() << "~SingletonDataBaseDestroyer";
    }

    void initialize(SingletonDataBase * p) { p_instance = p; };
};

class SingletonDataBase
{
private:
    static SingletonDataBase * p_instance;
    static SingletonDataBaseDestroyer destroyer;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
protected:
    SingletonDataBase() {
        qDebug() << "SingletonDataBase()\n";
        db.setDatabaseName("../server/user.db");

        if(!db.open())
            qDebug() << db.lastError().text();
        else qDebug() << "DB is open\n";
    }
    SingletonDataBase(const SingletonDataBase& ) = delete;
    SingletonDataBase& operator = (SingletonDataBase &) = delete;

    virtual ~SingletonDataBase() {
        db.close();
    }
    friend class SingletonDataBaseDestroyer;
public:
    static SingletonDataBase* getInstance() {
        if (!p_instance) {
            p_instance = new SingletonDataBase();
            destroyer.initialize(p_instance);
        }
        return p_instance;
    }

    QString queryToDB(QString mystrquery) {
        QSqlQuery query(db);

        query.exec(mystrquery);
        QSqlRecord rec = query.record();
        QString res = "";
        int numofcols = rec.count();
        while(query.next()) {
            for(int i=0;i<numofcols;i++)
                res.append("\t").append(query.value(i).toString());

            res.append("\n");
        }
        return res;
    }
};

#endif // DATABASE_H
