/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <QJsonArray>
#include <QJsonDocument>
#include <QMetaObject>
#include <QMetaProperty>

#include <nitroshare/jsonutil.h>

QJsonObject JsonUtil::objectToJson(QObject *object)
{
    QJsonObject jsonObject;
    for (int i = 1; i < object->metaObject()->propertyCount(); ++i) {
        auto property = object->metaObject()->property(i);
        auto name = property.name();
        auto value = object->property(name);
        if (property.type() == QVariant::LongLong) {
            value = QString::number(value.toLongLong());
        }
        jsonObject.insert(name, QJsonValue::fromVariant(value));
    }
    return jsonObject;
}

QByteArray JsonUtil::jsonValueToByteArray(const QJsonValue &value)
{
    switch (value.type()) {
    case QJsonValue::Array:
        return QJsonDocument(value.toArray()).toJson();
    case QJsonValue::Object:
        return QJsonDocument(value.toObject()).toJson();
    default:
    {
        QByteArray json = QJsonDocument(QJsonArray{value}).toJson().trimmed();
        return json.mid(1, json.length() - 2).trimmed() + "\n";
    }
    }
}
