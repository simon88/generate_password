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

#ifndef GENPASSWORD_H
#define GENPASSWORD_H

#include <QObject>
#include <QFlags>
#include <QString>

class genPassword : public QObject
{
    Q_OBJECT
public:
    enum Option { None        = 0x0,
                  Unique      = 0x1,
                  Unambiguous = 0x2,
                  Upper       = 0x4,
                  Number      = 0x8
    };

    Q_DECLARE_FLAGS(Options, Option)

    static QStringList genRandom(int length, QString &characterset, int amount, QFlags<Option> &flags);

};

Q_DECLARE_OPERATORS_FOR_FLAGS(genPassword::Options)

#endif // GENPASSWORD_H
