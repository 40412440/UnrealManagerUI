// Fill out your copyright notice in the Description page of Project Settings.

//
#include "LayerUI.h"
#include "Blueprint/UserWidget.h"

//
UE_DISABLE_OPTIMIZATION
void ULayerUI::PushToStack(UUserWidget* widget)
{
	if (widget)
	{
		OnWidgetPushed_Implementation();
		WidgetStack.Push(widget);

	}
	//WidgetPushedDelegate.Broadcast();
}

UUserWidget* ULayerUI::PopFromStack()
{
	if(WidgetStack.IsEmpty())
		return nullptr;

	UUserWidget* widget = WidgetStack.Pop();
	widget->SetVisibility(ESlateVisibility::Collapsed);
	OnWidgetPopped_Implementation();

	return widget;
}

void ULayerUI::SetVisibilityOfLayer(ESlateVisibility visibility)
{
	for (auto& widget : WidgetStack)
	{
		if (widget)
		{
			widget->SetVisibility(visibility);
		}
	}
	//LayerVisibilityChangedDelegate.Broadcast(visibility);
}

void ULayerUI::ClearStack()
{
	SetVisibilityOfLayer(ESlateVisibility::Collapsed);
	WidgetStack.Empty();
}

void ULayerUI::OnWidgetPushed_Implementation()
{
	switch (Type)
	{
	case SINGLE:
		SetVisibilityOfLayer(ESlateVisibility::Collapsed);
		//ClearStack();
		break;
	case MULTIPLE:

		break;
	default:
		break;
	}
}
void ULayerUI::OnWidgetPopped_Implementation()
{
	switch (Type)
	{
	case SINGLE:
		if (WidgetStack.IsEmpty())
			return;
		WidgetStack.Top()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case MULTIPLE:

		break;
	default:
		break;
	}
}
UE_ENABLE_OPTIMIZATION