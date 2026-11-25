#ifndef MAIN_FORM_H_
#define MAIN_FORM_H_

#include "../personnel_system.h"

namespace PersonnelGui {

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

public ref class MainForm : public Form {
 public:
  MainForm();
  ~MainForm();
  !MainForm();

 private:
  ServiceStatic* static_service_;
  ServiceDynamic* dynamic_service_;

  GroupBox^ grpInput_;
  RadioButton^ rbStatic_;
  RadioButton^ rbDynamic_;
  ComboBox^ cmbType_;
  TextBox^ txtId_;
  TextBox^ txtName_;
  TextBox^ txtSalary_;
  TextBox^ txtDetail_;
  TextBox^ txtMetric_;
  Button^ btnAdd_;
  Button^ btnRemove_;

  GroupBox^ grpActions_;
  Button^ btnSaveAll_;
  Button^ btnLoadAll_;
  Button^ btnDemoPolymorphism_;
  Button^ btnDemoExceptions_;
  Button^ btnDemoLab5_;
  Button^ btnDemoStl_;
  Button^ btnClearLog_;

  TabControl^ tabStorages_;
  TabPage^ tabStatic_;
  TabPage^ tabDynamic_;
  DataGridView^ dgvStatic_;
  DataGridView^ dgvDynamic_;

  GroupBox^ grpLog_;
  TextBox^ txtLog_;

  void InitializeComponent();
  DataGridView^ CreateStorageGrid();
  void RefreshGrids();
  void PopulateGrid(DataGridView^ grid, const ServiceStatic& service);
  void PopulateGrid(DataGridView^ grid, const ServiceDynamic& service);
  void AppendLog(String^ text);
  void ShowError(String^ message);

  String^ SelectedEmployeeTypeCode();
  int ParseIntField(TextBox^ box, String^ fieldName);
  double ParseDoubleField(TextBox^ box, String^ fieldName);

  void OnAddClick(Object^ sender, EventArgs^ e);
  void OnRemoveClick(Object^ sender, EventArgs^ e);
  void OnSaveAllClick(Object^ sender, EventArgs^ e);
  void OnLoadAllClick(Object^ sender, EventArgs^ e);
  void OnDemoPolymorphismClick(Object^ sender, EventArgs^ e);
  void OnDemoExceptionsClick(Object^ sender, EventArgs^ e);
  void OnDemoLab5Click(Object^ sender, EventArgs^ e);
  void OnDemoStlClick(Object^ sender, EventArgs^ e);
  void OnClearLogClick(Object^ sender, EventArgs^ e);
};

}  // namespace PersonnelGui

#endif  // MAIN_FORM_H_
