#include "MainForm.h"

#include <sstream>
#include <string>

#include "../lab5_templates.h"
#include "../project_management.h"
#include "../stl_lab.h"
#include "GuiHelpers.h"

namespace PersonnelGui {

namespace {

template <typename Service>
void PopulateGridImpl(DataGridView^ grid, const Service& service) {
  grid->Rows->Clear();
  for (std::size_t i = 0; i < service.Size(); ++i) {
    const Employee& emp = service.At(i);
    std::ostringstream details_stream;
    emp.Print(details_stream);

    array<Object^>^ row = gcnew array<Object^>{
        emp.GetId(),
        FromStdString(emp.GetType()),
        FromStdString(emp.GetName()),
        emp.GetSalary().ToString("F2"),
        FromStdString(details_stream.str())};
    grid->Rows->Add(row);
  }
}

TextBox^ AddLabeledTextBox(Control^ parent, String^ labelText, int labelX,
                           int inputX, int y, int width) {
  Label^ lbl = gcnew Label();
  lbl->Text = labelText;
  lbl->Location = Point(labelX, y + 3);
  lbl->AutoSize = true;
  parent->Controls->Add(lbl);

  TextBox^ box = gcnew TextBox();
  box->Location = Point(inputX, y);
  box->Size = Drawing::Size(width, 23);
  parent->Controls->Add(box);
  return box;
}

Button^ AddActionButton(Control^ parent, String^ text, int x, int y, int width,
                        EventHandler^ handler) {
  Button^ btn = gcnew Button();
  btn->Text = text;
  btn->Location = Point(x, y);
  btn->Size = Drawing::Size(width, 30);
  btn->Click += handler;
  parent->Controls->Add(btn);
  return btn;
}

}  // namespace

MainForm::MainForm()
    : static_service_(new ServiceStatic()),
      dynamic_service_(new ServiceDynamic()) {
  InitializeComponent();
  RefreshGrids();
}

MainForm::~MainForm() {
  this->!MainForm();
}

MainForm::!MainForm() {
  delete static_service_;
  static_service_ = nullptr;
  delete dynamic_service_;
  dynamic_service_ = nullptr;
}

void MainForm::InitializeComponent() {
  this->Text = L"Система управління персоналом (Windows Forms C++)";
  this->Size = Drawing::Size(980, 700);
  this->MinimumSize = Drawing::Size(860, 600);
  this->StartPosition = FormStartPosition::CenterScreen;

  // Input GroupBox
  grpInput_ = gcnew GroupBox();
  grpInput_->Text = L"Управління працівниками";
  grpInput_->Location = Point(12, 12);
  grpInput_->Size = Drawing::Size(460, 250);
  this->Controls->Add(grpInput_);

  Label^ lblStorage = gcnew Label();
  lblStorage->Text = L"Сховище:";
  lblStorage->Location = Point(14, 26);
  lblStorage->AutoSize = true;
  grpInput_->Controls->Add(lblStorage);

  rbStatic_ = gcnew RadioButton();
  rbStatic_->Text = L"Статичне (макс. 10)";
  rbStatic_->Location = Point(140, 24);
  rbStatic_->AutoSize = true;
  rbStatic_->Checked = true;
  grpInput_->Controls->Add(rbStatic_);

  rbDynamic_ = gcnew RadioButton();
  rbDynamic_->Text = L"Динамічне";
  rbDynamic_->Location = Point(290, 24);
  rbDynamic_->AutoSize = true;
  grpInput_->Controls->Add(rbDynamic_);

  Label^ lblType = gcnew Label();
  lblType->Text = L"Тип працівника:";
  lblType->Location = Point(14, 58);
  lblType->AutoSize = true;
  grpInput_->Controls->Add(lblType);

  cmbType_ = gcnew ComboBox();
  cmbType_->DropDownStyle = ComboBoxStyle::DropDownList;
  cmbType_->Location = Point(140, 55);
  cmbType_->Size = Drawing::Size(295, 23);
  cmbType_->Items->Add(L"1 - Розробник");
  cmbType_->Items->Add(L"2 - Тестувальник");
  cmbType_->Items->Add(L"3 - Менеджер");
  cmbType_->SelectedIndex = 0;
  grpInput_->Controls->Add(cmbType_);

  txtId_ = AddLabeledTextBox(grpInput_, L"ID:", 14, 140, 88, 120);
  txtName_ = AddLabeledTextBox(grpInput_, L"Ім'я:", 14, 140, 118, 295);
  txtSalary_ = AddLabeledTextBox(grpInput_, L"Зарплата:", 14, 140, 148, 120);
  txtDetail_ =
      AddLabeledTextBox(grpInput_, L"Спеціалізація:", 14, 140, 178, 295);
  txtMetric_ =
      AddLabeledTextBox(grpInput_, L"Показник (число):", 14, 140, 208, 120);

  btnAdd_ = AddActionButton(grpInput_, L"Додати", 275, 205, 78,
                            gcnew EventHandler(this, &MainForm::OnAddClick));
  btnRemove_ = AddActionButton(
      grpInput_, L"Видалити ID", 358, 205, 85,
      gcnew EventHandler(this, &MainForm::OnRemoveClick));

  // Actions GroupBox
  grpActions_ = gcnew GroupBox();
  grpActions_->Text = L"Файли та демонстрації";
  grpActions_->Location = Point(485, 12);
  grpActions_->Size = Drawing::Size(465, 250);
  grpActions_->Anchor = AnchorStyles::Top | AnchorStyles::Left |
                        AnchorStyles::Right;
  this->Controls->Add(grpActions_);

  btnSaveAll_ = AddActionButton(
      grpActions_, L"Зберегти обидва сховища", 16, 28, 205,
      gcnew EventHandler(this, &MainForm::OnSaveAllClick));
  btnLoadAll_ = AddActionButton(
      grpActions_, L"Завантажити обидва сховища", 235, 28, 210,
      gcnew EventHandler(this, &MainForm::OnLoadAllClick));

  btnDemoPolymorphism_ = AddActionButton(
      grpActions_, L"Поліморфізм", 16, 74, 205,
      gcnew EventHandler(this, &MainForm::OnDemoPolymorphismClick));
  btnDemoExceptions_ = AddActionButton(
      grpActions_, L"Виняткові ситуації", 235, 74, 210,
      gcnew EventHandler(this, &MainForm::OnDemoExceptionsClick));

  btnDemoLab5_ = AddActionButton(
      grpActions_, L"Лабораторна 5 (Оператори/Шаблони)", 16, 120, 205,
      gcnew EventHandler(this, &MainForm::OnDemoLab5Click));
  btnDemoStl_ = AddActionButton(
      grpActions_, L"STL-контейнери та функтори", 235, 120, 210,
      gcnew EventHandler(this, &MainForm::OnDemoStlClick));

  btnClearLog_ = AddActionButton(
      grpActions_, L"Очистити журнал", 16, 205, 429,
      gcnew EventHandler(this, &MainForm::OnClearLogClick));

  // Storage TabControl
  tabStorages_ = gcnew TabControl();
  tabStorages_->Location = Point(12, 272);
  tabStorages_->Size = Drawing::Size(938, 200);
  tabStorages_->Anchor = AnchorStyles::Top | AnchorStyles::Left |
                         AnchorStyles::Right;
  this->Controls->Add(tabStorages_);

  tabStatic_ = gcnew TabPage(L"Статичне сховище (ServiceStatic)");
  dgvStatic_ = CreateStorageGrid();
  tabStatic_->Controls->Add(dgvStatic_);
  tabStorages_->TabPages->Add(tabStatic_);

  tabDynamic_ = gcnew TabPage(L"Динамічне сховище (ServiceDynamic)");
  dgvDynamic_ = CreateStorageGrid();
  tabDynamic_->Controls->Add(dgvDynamic_);
  tabStorages_->TabPages->Add(tabDynamic_);

  // Output Log GroupBox
  grpLog_ = gcnew GroupBox();
  grpLog_->Text = L"Журнал та вивід демонстрацій";
  grpLog_->Location = Point(12, 480);
  grpLog_->Size = Drawing::Size(938, 170);
  grpLog_->Anchor = AnchorStyles::Top | AnchorStyles::Bottom |
                    AnchorStyles::Left | AnchorStyles::Right;
  this->Controls->Add(grpLog_);

  txtLog_ = gcnew TextBox();
  txtLog_->Multiline = true;
  txtLog_->ReadOnly = true;
  txtLog_->ScrollBars = ScrollBars::Vertical;
  txtLog_->Dock = DockStyle::Fill;
  txtLog_->Font = gcnew Drawing::Font(L"Consolas", 9.5f);
  grpLog_->Controls->Add(txtLog_);
}

DataGridView^ MainForm::CreateStorageGrid() {
  DataGridView^ grid = gcnew DataGridView();
  grid->Dock = DockStyle::Fill;
  grid->AllowUserToAddRows = false;
  grid->AllowUserToDeleteRows = false;
  grid->ReadOnly = true;
  grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
  grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
  grid->RowHeadersVisible = false;

  grid->Columns->Add(L"colId", L"ID");
  grid->Columns->Add(L"colType", L"Тип");
  grid->Columns->Add(L"colName", L"Ім'я");
  grid->Columns->Add(L"colSalary", L"Зарплата");
  grid->Columns->Add(L"colDetails", L"Повний опис");

  grid->Columns[0]->FillWeight = 10;
  grid->Columns[1]->FillWeight = 16;
  grid->Columns[2]->FillWeight = 20;
  grid->Columns[3]->FillWeight = 14;
  grid->Columns[4]->FillWeight = 40;
  return grid;
}

void MainForm::RefreshGrids() {
  PopulateGrid(dgvStatic_, *static_service_);
  PopulateGrid(dgvDynamic_, *dynamic_service_);
}

void MainForm::PopulateGrid(DataGridView^ grid, const ServiceStatic& service) {
  PopulateGridImpl(grid, service);
}

void MainForm::PopulateGrid(DataGridView^ grid,
                            const ServiceDynamic& service) {
  PopulateGridImpl(grid, service);
}

void MainForm::AppendLog(String^ text) {
  if (String::IsNullOrEmpty(text)) {
    return;
  }
  String^ normalized = text->Replace(L"\r\n", L"\n")->Replace(L"\n", L"\r\n");
  txtLog_->AppendText(normalized);
  if (!normalized->EndsWith(L"\r\n")) {
    txtLog_->AppendText(L"\r\n");
  }
}

void MainForm::ShowError(String^ message) {
  AppendLog(L"[Помилка] " + message);
  MessageBox::Show(this, message, L"Помилка", MessageBoxButtons::OK,
                   MessageBoxIcon::Error);
}

String^ MainForm::SelectedEmployeeTypeCode() {
  return (cmbType_->SelectedIndex + 1).ToString();
}

int MainForm::ParseIntField(TextBox^ box, String^ fieldName) {
  int value = 0;
  if (!Int32::TryParse(box->Text->Trim(), value)) {
    throw ValidationException(ToStdString(fieldName + L" має бути цілим числом"));
  }
  return value;
}

double MainForm::ParseDoubleField(TextBox^ box, String^ fieldName) {
  double value = 0.0;
  if (!Double::TryParse(box->Text->Trim(),
                        System::Globalization::NumberStyles::Float,
                        System::Globalization::CultureInfo::InvariantCulture,
                        value) &&
      !Double::TryParse(box->Text->Trim(), value)) {
    throw ValidationException(ToStdString(fieldName + L" має бути числом"));
  }
  return value;
}

void MainForm::OnAddClick(Object^ sender, EventArgs^ e) {
  try {
    std::string type = ToStdString(SelectedEmployeeTypeCode());
    int id = ParseIntField(txtId_, L"ID");
    std::string name = ToStdString(txtName_->Text->Trim());
    double salary = ParseDoubleField(txtSalary_, L"Зарплата");
    std::string detail = ToStdString(txtDetail_->Text->Trim());
    int metric = ParseIntField(txtMetric_, L"Показник");

    auto employee = CreateEmployee(type, id, name, salary, detail, metric);
    if (rbStatic_->Checked) {
      static_service_->Add(std::move(employee));
      tabStorages_->SelectedTab = tabStatic_;
      AppendLog(L"Працівника додано до статичного сховища.");
    } else {
      dynamic_service_->Add(std::move(employee));
      tabStorages_->SelectedTab = tabDynamic_;
      AppendLog(L"Працівника додано до динамічного сховища.");
    }
    RefreshGrids();
  } catch (const PersonnelException& error) {
    ShowError(FromStdString(error.what()));
  }
}

void MainForm::OnRemoveClick(Object^ sender, EventArgs^ e) {
  try {
    int id = ParseIntField(txtId_, L"ID");
    if (rbStatic_->Checked) {
      static_service_->RemoveById(id);
      AppendLog(L"Видалено зі статичного сховища ID=" + id.ToString());
    } else {
      dynamic_service_->RemoveById(id);
      AppendLog(L"Видалено з динамічного сховища ID=" + id.ToString());
    }
    RefreshGrids();
  } catch (const PersonnelException& error) {
    ShowError(FromStdString(error.what()));
  }
}

void MainForm::OnSaveAllClick(Object^ sender, EventArgs^ e) {
  try {
    static_service_->SaveAll("static_personnel.txt");
    dynamic_service_->SaveAll("dynamic_personnel.txt");
    AppendLog(L"Дані збережено у static_personnel.txt та dynamic_personnel.txt.");
  } catch (const PersonnelException& error) {
    ShowError(FromStdString(error.what()));
  }
}

void MainForm::OnLoadAllClick(Object^ sender, EventArgs^ e) {
  try {
    static_service_->LoadAll("static_personnel.txt");
    dynamic_service_->LoadAll("dynamic_personnel.txt");
    RefreshGrids();
    AppendLog(L"Дані завантажено з файлів.");
  } catch (const PersonnelException& error) {
    ShowError(FromStdString(error.what()));
  }
}

void MainForm::OnDemoPolymorphismClick(Object^ sender, EventArgs^ e) {
  try {
    CoutRedirector redirector;
    if (dynamic_service_->Size() > 0) {
      DemonstratePolymorphism(dynamic_service_->At(0));
    } else if (static_service_->Size() > 0) {
      DemonstratePolymorphism(static_service_->At(0));
    } else {
      AppendLog(L"Спочатку додайте працівника.");
      return;
    }
    AppendLog(FromStdString(redirector.GetOutput()));
  } catch (const PersonnelException& error) {
    ShowError(FromStdString(error.what()));
  }
}

void MainForm::OnDemoExceptionsClick(Object^ sender, EventArgs^ e) {
  CoutRedirector redirector;
  DemonstrateExceptions();
  AppendLog(FromStdString(redirector.GetOutput()));
}

void MainForm::OnDemoLab5Click(Object^ sender, EventArgs^ e) {
  CoutRedirector redirector;

  ProjectModule first("Авторизація", 4, 12000.0);
  ProjectModule second("Звіти", 2, 8000.0);
  std::cout << "Початкові модулі:\n";
  first.PrintInfo();
  second.PrintInfo();

  ProjectModule postfix_increment = first++;
  ++first;
  ProjectModule postfix_decrement = first--;
  --first;
  std::cout << "Постфіксний ++ повернув:\n";
  postfix_increment.PrintInfo();
  std::cout << "Постфіксний -- повернув:\n";
  postfix_decrement.PrintInfo();
  std::cout << "Стан після префіксних операцій:\n";
  first.PrintInfo();

  ProjectModule sum = first + second;
  ProjectModule difference = first - second;
  ProjectModule product = first * 1.5;
  ProjectModule quotient = first / 2.0;
  std::cout << "Оператори +, -, *, /:\n";
  sum.PrintInfo();
  difference.PrintInfo();
  product.PrintInfo();
  quotient.PrintInfo();

  first += second;
  first -= second;
  first *= 2.0;
  first /= 2.0;
  std::cout << "Стан після +=, -=, *=, /=:\n";
  first.PrintInfo();

  std::cout << "Шаблонна функція GreaterValue: "
            << ProjectModule::GreaterValue(24, 17) << '\n';
  ProjectRecord<int, std::string, ProjectModule, double, bool> record(
      501, "Шаблонний запис", first, 94.5, true);
  std::cout << "Шаблонний клас з п'ятьма типами: ID=" << record.GetId()
            << ", назва=" << record.GetName()
            << ", метрика=" << record.GetMetric()
            << ", активний=" << (record.GetState() ? "так" : "ні") << '\n';
  std::cout << "Користувацький тип ProjectModule у шаблоні:\n";
  record.GetObject().PrintInfo();

  AppendLog(FromStdString(redirector.GetOutput()));
}

void MainForm::OnDemoStlClick(Object^ sender, EventArgs^ e) {
  CoutRedirector redirector;
  DemonstrateStlContainers();
  AppendLog(FromStdString(redirector.GetOutput()));
}

void MainForm::OnClearLogClick(Object^ sender, EventArgs^ e) {
  txtLog_->Clear();
}

}  // namespace PersonnelGui
