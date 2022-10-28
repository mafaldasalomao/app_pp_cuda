#include<iostream>
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <iomanip>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include "device_launch_parameters.h"
#include "GpuSolver.h"
#include "filters_CPU.cpp"
#include <chrono>
using namespace std::chrono;
//Load Images
#define STB_IMAGE_IMPLEMENTATION
// Write Images
#define STB_IMAGE_WRITE_IMPLEMENTATION

//#define STBIR_INCLUDE_STB_IMAGE_RESIZE_H

#include "include/stb_image.h"
//#include "include/stb_image_resize.h"
#include "include/stb_image_write.h"

namespace Project3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Sumário para MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Adicione o código do construtor aqui
			//
		}

	protected:
		/// <summary>
		/// Limpar os recursos que estão sendo usados.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ load;
	protected:


	private: System::Windows::Forms::Button^ exit;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Button^ close;
	private: System::Windows::Forms::Label^ time_exec;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Button^ convertToGray;
	protected:

	private:
		/// <summary>
		/// Variável de designer necessária.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necessário para suporte ao Designer - não modifique 
		/// o conteúdo deste método com o editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->load = (gcnew System::Windows::Forms::Button());
			this->exit = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->close = (gcnew System::Windows::Forms::Button());
			this->time_exec = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->convertToGray = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// load
			// 
			this->load->Location = System::Drawing::Point(59, 37);
			this->load->Name = L"load";
			this->load->Size = System::Drawing::Size(156, 54);
			this->load->TabIndex = 0;
			this->load->Text = L"Load IMG";
			this->load->UseVisualStyleBackColor = true;
			this->load->Click += gcnew System::EventHandler(this, &MyForm::load_Click);
			// 
			// exit
			// 
			this->exit->Location = System::Drawing::Point(1145, 12);
			this->exit->Name = L"exit";
			this->exit->Size = System::Drawing::Size(151, 47);
			this->exit->TabIndex = 2;
			this->exit->Text = L"Exit";
			this->exit->UseVisualStyleBackColor = true;
			this->exit->Click += gcnew System::EventHandler(this, &MyForm::exit_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(41, 152);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(625, 625);
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(699, 151);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(625, 625);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			// 
			// close
			// 
			this->close->Location = System::Drawing::Point(221, 37);
			this->close->Name = L"close";
			this->close->Size = System::Drawing::Size(142, 54);
			this->close->TabIndex = 5;
			this->close->Text = L"Close IMG";
			this->close->UseVisualStyleBackColor = true;
			this->close->Click += gcnew System::EventHandler(this, &MyForm::close_Click);
			// 
			// time_exec
			// 
			this->time_exec->AutoSize = true;
			this->time_exec->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->time_exec->Location = System::Drawing::Point(694, 113);
			this->time_exec->Name = L"time_exec";
			this->time_exec->Size = System::Drawing::Size(97, 25);
			this->time_exec->TabIndex = 6;
			this->time_exec->Text = L"Velocity : ";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(59, 113);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(58, 20);
			this->checkBox1->TabIndex = 7;
			this->checkBox1->Text = L"GPU";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// convertToGray
			// 
			this->convertToGray->Location = System::Drawing::Point(369, 37);
			this->convertToGray->Name = L"convertToGray";
			this->convertToGray->Size = System::Drawing::Size(158, 54);
			this->convertToGray->TabIndex = 8;
			this->convertToGray->Text = L"GrayScale";
			this->convertToGray->UseVisualStyleBackColor = true;
			this->convertToGray->Click += gcnew System::EventHandler(this, &MyForm::convertToGray_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1374, 839);
			this->Controls->Add(this->convertToGray);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->time_exec);
			this->Controls->Add(this->close);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->exit);
			this->Controls->Add(this->load);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void load_Click(System::Object^ sender, System::EventArgs^ e) {

		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		//insert here the filter if you want
		//ofd->Filter..
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

			//img_input->Image = Image::FromFile(ofd->FileName);
			//System::String^ strFilename = ofd->FileName;

			pictureBox1->ImageLocation = ofd->FileName;

		}
		/*useGPU obj;
		int c[5] = {};
		int a[5] = { 0, 1, 2, 3, 4 };
		int b[5] = { 10, 11, 12, 13, 14 };

		obj.adding(c, a, b, 5);
		textBox1->Text = System::Convert::ToString(c[0]);*/
	}
	private: System::Void exit_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	private: System::Void close_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBox1->ImageLocation = "";
		pictureBox2->Image = nullptr;
	}
private: System::Void convertToGray_Click(System::Object^ sender, System::EventArgs^ e) {
	useGPU obj;
	System::String^ file = pictureBox1->ImageLocation;
	std::string converted_xyz = msclr::interop::marshal_as< std::string >(file);
	int width, height, channels;
	const char* c = converted_xyz.c_str();
	unsigned char* img = stbi_load(c, &width, &height, &channels, 4);
	auto start = high_resolution_clock::now();
	if (checkBox1->Checked) {
		obj.ImageToGrayGpu(img, width, height);
	}
	else {
		ConvertImageToGrayCpu(img, width, height);
	}
	
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	time_exec->Text = "Velocity : " + duration.count() + " microseconds";
	stbi_write_jpg("images/output.jpg", width, height, 4, img, 100);
	pictureBox2->ImageLocation = "images/output.jpg";
	stbi_image_free(img);
}
};
}
