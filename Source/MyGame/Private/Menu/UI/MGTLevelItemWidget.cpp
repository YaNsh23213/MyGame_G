// MyGameTry, All Rights Reserved


#include "Menu/UI/MGTLevelItemWidget.h"
#include"Components/Button.h"
#include"Components/TextBlock.h"
#include"Components/Image.h"

void UMGTLevelItemWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &UMGTLevelItemWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &UMGTLevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &UMGTLevelItemWidget::OnLevelItemUnhovered);
    }
}
void UMGTLevelItemWidget::OnLevelItemClicked() 
{
    OnLevelSelected.Broadcast(LevelData);
}
void UMGTLevelItemWidget::SetLevelData(const FLevelData& Data) 
{
    LevelData = Data;
    if(LevelNameTextBlock) 
    {
        LevelNameTextBlock->SetText(FText::FromName(Data.LelelDisplayName));
    }

    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.LevelThumb);
    }
}
void UMGTLevelItemWidget::SetSelected(bool IsSelected) 
{
    if (LevelImage)
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}


void UMGTLevelItemWidget::OnLevelItemHovered() 
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}


void UMGTLevelItemWidget::OnLevelItemUnhovered() 
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}