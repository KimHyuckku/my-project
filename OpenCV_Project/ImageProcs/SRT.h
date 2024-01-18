#pragma once

namespace SpeechRecognitionTutorial {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// SRT에 대한 요약입니다.
	/// </summary>
	public ref class SRT : public System::Windows::Forms::Form
	{
	public:
		SRT(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~SRT()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ HeadingLabel;
	private: System::Windows::Forms::TextBox^ TextBox;


	private: System::Windows::Forms::Button^ SpeakButton;
	private: System::Windows::Forms::Button^ PauseButton;
	private: System::Windows::Forms::Button^ StopButton;
		   System::Speech::Synthesis::SpeechSynthesizer speech_synthesizer;
		   bool paused = false;



	protected:

	protected:

	private:
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		void InitializeComponent(void)
		{
			this->HeadingLabel = (gcnew System::Windows::Forms::Label());
			this->TextBox = (gcnew System::Windows::Forms::TextBox());
			this->SpeakButton = (gcnew System::Windows::Forms::Button());
			this->PauseButton = (gcnew System::Windows::Forms::Button());
			this->StopButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// HeadingLabel
			// 
			this->HeadingLabel->AutoSize = true;
			this->HeadingLabel->Font = (gcnew System::Drawing::Font(L"궁서체", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(129)));
			this->HeadingLabel->Location = System::Drawing::Point(25, 29);
			this->HeadingLabel->Name = L"HeadingLabel";
			this->HeadingLabel->Size = System::Drawing::Size(154, 21);
			this->HeadingLabel->TabIndex = 0;
			this->HeadingLabel->Text = L"Text->speech";
			this->HeadingLabel->Click += gcnew System::EventHandler(this, &SRT::label1_Click);
			// 
			// TextBox
			// 
			this->TextBox->Location = System::Drawing::Point(29, 82);
			this->TextBox->Multiline = true;
			this->TextBox->Name = L"TextBox";
			this->TextBox->Size = System::Drawing::Size(478, 359);
			this->TextBox->TabIndex = 1;
			// 
			// SpeakButton
			// 
			this->SpeakButton->Location = System::Drawing::Point(561, 82);
			this->SpeakButton->Name = L"SpeakButton";
			this->SpeakButton->Size = System::Drawing::Size(75, 23);
			this->SpeakButton->TabIndex = 2;
			this->SpeakButton->Text = L"Speak";
			this->SpeakButton->UseVisualStyleBackColor = true;
			this->SpeakButton->Click += gcnew System::EventHandler(this, &SRT::SpeakButton_Click);
			// 
			// PauseButton
			// 
			this->PauseButton->Location = System::Drawing::Point(561, 111);
			this->PauseButton->Name = L"PauseButton";
			this->PauseButton->Size = System::Drawing::Size(75, 23);
			this->PauseButton->TabIndex = 3;
			this->PauseButton->Text = L"Pause";
			this->PauseButton->UseVisualStyleBackColor = true;
			this->PauseButton->Click += gcnew System::EventHandler(this, &SRT::PauseButton_Click);
			// 
			// StopButton
			// 
			this->StopButton->Location = System::Drawing::Point(561, 140);
			this->StopButton->Name = L"StopButton";
			this->StopButton->Size = System::Drawing::Size(75, 23);
			this->StopButton->TabIndex = 4;
			this->StopButton->Text = L"Stop";
			this->StopButton->UseVisualStyleBackColor = true;
			this->StopButton->Click += gcnew System::EventHandler(this, &SRT::StopButton_Click);
			// 
			// SRT
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(673, 484);
			this->Controls->Add(this->StopButton);
			this->Controls->Add(this->PauseButton);
			this->Controls->Add(this->SpeakButton);
			this->Controls->Add(this->TextBox);
			this->Controls->Add(this->HeadingLabel);
			this->Name = L"SRT";
			this->Text = L"SRT";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void SpeakButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (paused)
		{
			speech_synthesizer.Resume();
			paused = false;

			PauseButton->Text = "Pause";
		}
		speech_synthesizer.SpeakAsyncCancelAll();
		speech_synthesizer.SpeakAsync(TextBox->Text);
	}
	private: System::Void StopButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		speech_synthesizer.SpeakAsyncCancelAll();
	}
	private: System::Void PauseButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (paused)
		{
			speech_synthesizer.Resume();
			paused = false;

			PauseButton->Text = "Pause";
		}
		else
		{
			speech_synthesizer.Pause();
			paused = true;

			PauseButton->Text = "Resume";
		}
	}
};
}
