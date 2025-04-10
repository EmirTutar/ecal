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

#pragma once

#include <vector>

#include <QAbstractItemModel>

#include <ecal/ecal.h>

class SeverityModel : public QAbstractListModel
{
  Q_OBJECT

public:
  SeverityModel(QObject *parent = nullptr, bool include_unknown_severity = false);
  ~SeverityModel();

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  QString getString(int row) const;
  eCAL::Process::eSeverity getSeverity(int row) const;

  int getRow(eCAL::Process::eSeverity severity) const;

private:
  std::vector<std::pair<QString, eCAL::Process::eSeverity>> rows;
};