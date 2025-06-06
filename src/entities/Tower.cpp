// ================================================================================================
// File: Tower.cpp
// Author: Luka Vukorepa (https://github.com/lukav1607)
// Created: April 29, 2025
// Description: Defines the Tower class, which is a base class for all tower types in the game.
//              It contains common attributes and methods for all tower types.
// ================================================================================================
// License: MIT License
// Copyright (c) 2025 Luka Vukorepa
// ================================================================================================

#include "Tower.hpp"

Tower::Tower(TowerRegistry::Type type, sf::Color color, sf::Color color2, sf::Color color3, sf::Vector2i tilePosition) :
	isSelected(false),
	type(type),
	towerColor(color),
	position(Utility::tileToPixelPosition(tilePosition)),
	timeSinceLastShot(0.f),
	bulletSpeed(0.f),
	level(0),
	m_isMarkedForSale(false),
	m_isMarkedForUpgrade(false),
	isRangeCircleVisible(false)
{
	// Fetch the tower metadata attributes from the registry
	const TowerRegistry::TowerMetadata& metadata = TowerRegistry::getTowerMetadataRegistry()[static_cast<int>(type)];
	attributes = metadata.attributes;

	shape.setSize({ 80.f, 80.f });
	shape.setFillColor(towerColor);
	shape.setOrigin({ shape.getSize().x / 2.f, shape.getSize().y / 2.f });
	shape.setPosition(position);

	shape2.setSize({ 60.f, 60.f });
	shape2.setFillColor(color2);
	shape2.setOrigin({ shape2.getSize().x / 2.f, shape2.getSize().y / 2.f });
	shape2.setPosition(position);

	shape3.setSize({ 40.f, 40.f });
	shape3.setFillColor(color3);
	shape3.setOrigin({ shape3.getSize().x / 2.f, shape3.getSize().y / 2.f });
	shape3.setPosition(position);

	rangeCircle.setRadius(attributes.at(level).range);
	rangeCircle.setOrigin({ rangeCircle.getRadius(), rangeCircle.getRadius() });
	rangeCircle.setFillColor(sf::Color(0, 0, 0, 15));
	rangeCircle.setOutlineColor(sf::Color(0, 0, 0, 50));
	rangeCircle.setOutlineThickness(2.f);
	rangeCircle.setPosition(position);
	rangeCircle.setPointCount(100);
}

bool Tower::tryUpgrade(int gold)
{
	if (level >= getMaxLevel())
		return false;

	if (gold >= attributes.at(static_cast<size_t>(level + 1)).buyCost)
	{
		level++;
		rangeCircle.setRadius(attributes.at(level).range);
		rangeCircle.setOrigin({ rangeCircle.getRadius(), rangeCircle.getRadius() });
		rangeCircle.setPosition(position);
		m_isMarkedForUpgrade = false;
		return true;
	}
	return false;
}

void Tower::updateSelectionOutline()
{
	if (isSelected)
	{
		shape.setOutlineColor(sf::Color(255, 255, 255, 255));
		shape.setOutlineThickness(4.f);
	}
	else
	{
		shape.setOutlineColor(sf::Color(0, 0, 0, 0));
		shape.setOutlineThickness(0.f);
	}
}