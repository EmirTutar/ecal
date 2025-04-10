/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2025 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

#include "severity_model.h"

SeverityModel::SeverityModel(QObject *parent, bool include_unknown_severity)
  : QAbstractListModel(parent)
{
  if (include_unknown_severity)
  {
    rows.push_back(std::make_pair(QString("Unknown"), eCAL::Process::eSeverity::unknown));
  }
  rows.push_back(std::make_pair(QString("Healthy"), eCAL::Process::eSeverity::healthy));
  rows.push_back(std::make_pair(QString("Warning"), eCAL::Process::eSeverity::warning));
  rows.push_back(std::make_pair(QString("Critical"), eCAL::Process::eSeverity::critical));
  rows.push_back(std::make_pair(QString("Failed"), eCAL::Process::eSeverity::failed));
}

SeverityModel::~SeverityModel()
{}

int SeverityModel::rowCount(const QModelIndex& /*parent*/) const
{
  return (int)rows.size();
}

QVariant SeverityModel::data(const QModelIndex& index, int role) const
{
  if (role == Qt::ItemDataRole::DisplayRole)
  {
    return rows[index.row()].first;
  }
  return QVariant();
}

QString SeverityModel::getString(int row) const
{
  return rows[row].first;
}

eCAL::Process::eSeverity SeverityModel::getSeverity(int row) const
{
  return rows[row].second;
}

int SeverityModel::getRow(eCAL::Process::eSeverity severity) const
{
  for (int i = 0; i < (int)rows.size(); i++)
  {
    if (rows[i].second == severity)
      return i;
  }
  return -1;
}