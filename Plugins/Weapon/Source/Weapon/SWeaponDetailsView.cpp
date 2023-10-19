#include "SWeaponDetailsView.h"
#include "Weapon/CWeaponAsset.h"
#include "SWeaponHitData.h"
#include "SWeaponEquipmentData.h"
#include "SWeaponDoActionData.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "IDetailPropertyRow.h"
#include "SWeaponCheckBoxes.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "SWeaponAirActionData.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundWave.h"
#include "Camera/CameraShake.h"

bool SWeaponDetailsView::bRefreshByCheckBoxes = false;

TSharedRef<IDetailCustomization> SWeaponDetailsView::MakeInstance()
{
	return MakeShareable(new SWeaponDetailsView());
}

void SWeaponDetailsView::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	UClass* type = UCWeaponAsset::StaticClass();

	//DetailBuilder.HideCategory("CWeaponAsset");

	//Class Setting
	{
		IDetailCategoryBuilder& category =  DetailBuilder.EditCategory("ClassSettings", FText::FromString("Class Settings"));
		category.AddProperty("AttachmentClass", type);
		category.AddProperty("EquipmentClass", type);
		category.AddProperty("DoActionClass", type);
		category.AddProperty("SubActionClass", type);
		category.AddProperty("SkillActionClass", type);
	}

	//EquipmentData	
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("EquipmentData", FText::FromString("Equipment Data"));
		IDetailPropertyRow& row =  category.AddProperty("EquipmentData", type);

		if(bRefreshByCheckBoxes == false)
		{
			TSharedPtr<SWeaponCheckBoxes> checkBoxes = SWeaponEquipmentData::CreateCheckBoxes();
			checkBoxes->AddProperties(row.GetPropertyHandle());

			FEquipmentData data;

			int32 index = 0;
			checkBoxes->CheckDefaultObject(index++, data.Montage);
			checkBoxes->CheckDefaultValue(index++, data.PlayRate);
			checkBoxes->CheckDefaultValue(index++, data.bCanMove);
			checkBoxes->CheckDefaultValue(index++, data.bUseControlRotation);
		}
		
	}

	//DoAction Data	
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("DoActionData", FText::FromString("DoAction Data"));
		IDetailPropertyRow& row = category.AddProperty("DoActionDatas", type); // ������ �߰��� ������ DoActionDatas

		//���ΰ�ħ �ƴ���
		if (bRefreshByCheckBoxes == false)
		{
			// ��� ���ư������� �˾ƾ� �� ���̴�.
			uint32 count = 0;
			row.GetPropertyHandle()->GetNumChildren(count);

			// ���� ���� �� üũ�ڽ��� ����־�� �Ѵ�.
			SWeaponDoActionData::EmptyCheckBoxes();

			FDoActionData data;

			for (uint32 i = 0; i < count; i++)
			{
				TSharedPtr<IPropertyHandle> handle = row.GetPropertyHandle()->GetChildHandle(i);

				TSharedPtr<SWeaponCheckBoxes> checkBoxes = SWeaponDoActionData::AddCheckBoxes();
				checkBoxes->AddProperties(handle);

				int32 index = 0;
				checkBoxes->CheckDefaultObject(index++, data.Montage);
				checkBoxes->CheckDefaultValue(index++, data.PlayRate);
				checkBoxes->CheckDefaultValue(index++, data.ManaPoint);
				checkBoxes->CheckDefaultValue(index++, data.CoolTime);
				checkBoxes->CheckDefaultValue(index++, data.bCanMove);
				checkBoxes->CheckDefaultValue(index++, data.bFixedCamera);
				checkBoxes->CheckDefaultObject(index++, data.Effect);
				checkBoxes->CheckDefaultValue(index++, data.EffectLocation);
				checkBoxes->CheckDefaultValue(index++, data.EffectScale);
			}
		}// if(bRefreshByCheckBoxes)
	}

	//Hit Data	
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("HitData", FText::FromString("Hit Data"));
		IDetailPropertyRow& row = category.AddProperty("HitDatas", type); // ������ �߰��� ������ HitDatas

		//���ΰ�ħ �ƴ���
		if (bRefreshByCheckBoxes == false)
		{
			// ��� ���ư������� �˾ƾ� �� ���̴�.
			uint32 count = 0;
			row.GetPropertyHandle()->GetNumChildren(count);

			// ���� ���� �� üũ�ڽ��� ����־�� �Ѵ�.
			SWeaponHitData::EmptyCheckBoxes();

			FHitData data;

			for (uint32 i = 0; i < count; i++)
			{
				TSharedPtr<IPropertyHandle> handle = row.GetPropertyHandle()->GetChildHandle(i);

				TSharedPtr<SWeaponCheckBoxes> checkBoxes = SWeaponHitData::AddCheckBoxes();
				checkBoxes->AddProperties(handle);

				int32 index = 0;
				checkBoxes->CheckDefaultObject(index++, data.Montage);
				checkBoxes->CheckDefaultValue(index++, data.PlayRate);
				checkBoxes->CheckDefaultValue(index++, data.ManaPoint);
				checkBoxes->CheckDefaultValue(index++, data.Power);
				checkBoxes->CheckDefaultValue(index++, data.Launch);
				checkBoxes->CheckDefaultValue(index++, data.StopTime);
				checkBoxes->CheckDefaultObject(index++, data.CameraShake);
				checkBoxes->CheckDefaultObject(index++, data.Sound);
				checkBoxes->CheckDefaultObject(index++, data.Effect);
				checkBoxes->CheckDefaultValue(index++, data.EffectLocation);
				checkBoxes->CheckDefaultValue(index++, data.EffectScale);
			}
		}// if(bRefreshByCheckBoxes)
	}
}