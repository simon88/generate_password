/*
    Copyright 2015 Barotte Simon <simon.barotte@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "genpassword.h"
#include "random.h"
#include <QString>


QStringList genPassword::genRandom(int length, QString &characterset, int amount, QFlags<Option> &flags)
{
    QStringList pwd_list;

    if (length > characterset.length() && flags & Unique)
    {
        qDebug() << "Impossible de créer un mot de passe avec des caractères uniques";
        return QStringList();
    }

    for(int i=0; i<amount; i++)
    {
        QString password;
        QString cs = characterset;
        while (password.length() < length)
        {
            int index = Random::nextInt(cs.length());
            password.append(cs[index]);
            if (flags & Unique)
            {
                cs.remove(index, 1);
            }
        }
        pwd_list.append(password);
    }

    return pwd_list;
}

