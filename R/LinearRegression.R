#setting path
setwd(dirname(rstudioapi::getActiveDocumentContext()$path))
setwd("../data/")

#lib
library(lmtest)
library(MASS)
library(car)

#POPULATION
dfPop = read.csv2("population.csv")
names(dfPop)[names(dfPop) == "WORLD..by.thousands."] = "Population"
dfPop$Population = gsub('\\s+','',dfPop$Population)
dfPop$Population = gsub(',','',dfPop$Population)
dfPop$Population = as.numeric(dfPop$Population) * 100
dfPop$Population = round(dfPop$Population / 10**10,digits = 2)
head(dfPop)

plot(dfPop)
boxplot(dfPop$Population)

resPop = lm(Population ~ Year, dfPop)
par(mfrow=c(2,2))
plot(resPop)
abs(rstudent(resPop))[abs(rstudent(resPop))>2]
shapiro.test(resPop$residuals)

dfPop2 = dfPop[-c(1,2,3,4,5,6),]
resPop = lm(Population ~ Year, dfPop2)
plot(resPop)
shapiro.test(resPop$residuals)

bc = boxcox(dfPop2$Population~dfPop2$Year)
lambda = bc$x[which.max(bc$y)]
print(lambda)

bptest(resPop)
ncvTest(resPop)
summary(resPop)

par(mfrow=c(1,1))
plot(dfPop2)
abline(resPop,col = "red",lwd = 2)

#GDP
dfGDP = read.csv2("gdp.csv")
names(dfGDP)[names(dfGDP) == "GDP.in.billion.of.dollars"] = "GDP"
dfGDP$GDP = gsub('\\.','',dfGDP$GDP)
dfGDP$GDP = gsub(',','',dfGDP$GDP)
dfGDP$GDP = as.numeric(dfGDP$GDP) * 10000000
dfGDP$GDP = round(dfGDP$GDP / 10**13,digits = 2)
dfGDP = dfGDP [seq(dim(dfGDP)[1],1),]
head(dfGDP)

plot(dfGDP)
boxplot(dfGDP$GDP)

resGDP = lm(GDP ~ Year, dfGDP)
par(mfrow=c(2,2))
plot(resGDP)
abs(rstudent(resGDP))[abs(rstudent(resGDP))>2]
shapiro.test(resGDP$residuals)

bc = boxcox(dfGDP$GDP~dfGDP$Year)
lambda = bc$x[which.max(bc$y)]
print(lambda)

resGDP = lm(log(GDP) ~ Year, dfGDP)
plot(resGDP)
abs(rstudent(resGDP))[abs(rstudent(resGDP))>2]
shapiro.test(resGDP$residuals)

bptest(resGDP)
ncvTest(resGDP)
summary(resGDP)

par(mfrow=c(1,1))
plot(dfGDP$Year,log(dfGDP$GDP))
abline(resGDP,col = "red",lwd = 2)

#CO2
dfCO2 = read.csv2("co2.csv",sep = ',')
dfCO2$Entity = NULL
dfCO2$Code = NULL
names(dfCO2)[names(dfCO2) == "Fossil.fuel...land.use.emissions..GtCO2."] = "GtCO2"
dfCO2$GtCO2 = as.numeric(dfCO2$Land.use.emissions..GtCO2.) + as.numeric(dfCO2$Fossil.fuel.and.industry.emissions..GtCO2.)
dfCO2$Land.use.emissions..GtCO2. = NULL
dfCO2$Fossil.fuel.and.industry.emissions..GtCO2. = NULL
dfCO2$GtCO2 = round(dfCO2$GtCO2 / 10**9,digits = 2)
head(dfCO2)

plot(dfCO2)
boxplot(dfCO2$GtCO2)

resCO2 = lm(GtCO2 ~ Year,dfCO2)
par(mfrow=c(2,2))
plot(resCO2)
abs(rstudent(resCO2))[abs(rstudent(resCO2))>2]
shapiro.test(resCO2$residuals)

dfCO22 = dfCO2[-c(37),]
resCO2 = lm(GtCO2 ~ Year, dfCO22)
plot(resCO2)
shapiro.test(resCO2$residuals)

bc = boxcox(dfCO22$GtCO2~dfCO22$Year)
lambda = bc$x[which.max(bc$y)]
print(lambda)

resCO2 = lm(sqrt(GtCO2) ~ Year, dfCO22)
plot(resCO2)
shapiro.test(resCO2$residuals)

bptest(resCO2)
ncvTest(resCO2)

par(mfrow=c(1,1))
plot(dfCO22$Year,sqrt(dfCO22$GtCO2))
abline(resCO2,col = "red",lwd = 2)

#ENERGY
dfEnergy = read.csv2("energy.csv",sep = ',')
dfEnergy$Entity = NULL
dfEnergy$Code = NULL
names(dfEnergy)[names(dfEnergy) == "Wind"] = "TWhEnergy"
dfEnergy$TWhEnergy = dfEnergy$TWhEnergy + dfEnergy$Oil + dfEnergy$Nuclear + dfEnergy$Hydropower + dfEnergy$Traditional.bimass + dfEnergy$Other.renewables + dfEnergy$Biofuels + dfEnergy$Solar + dfEnergy$Coal + dfEnergy$Gas
dfEnergy$Oil = NULL
dfEnergy$Nuclear = NULL
dfEnergy$Hydropower = NULL
dfEnergy$Traditional.bimass = NULL 
dfEnergy$Other.renewables = NULL
dfEnergy$Biofuels = NULL
dfEnergy$Solar = NULL
dfEnergy$Coal = NULL
dfEnergy$Gas = NULL
dfEnergy$TWhEnergy = round(dfEnergy$TWhEnergy / 10**3,digits = 2)
head(dfEnergy)

plot(dfEnergy)
boxplot(dfEnergy$TWhEnergy)

resEnergy = lm(TWhEnergy ~ Year,dfEnergy)
par(mfrow=c(2,2))
plot(resEnergy)
abs(rstudent(resEnergy))[abs(rstudent(resEnergy))>2]
shapiro.test(resEnergy$residuals)

bc = boxcox(dfEnergy$TWhEnergy~dfEnergy$Year)
lambda = bc$x[which.max(bc$y)]
print(lambda)

resEnergy = lm(sqrt(TWhEnergy) ~ Year,dfEnergy)
plot(resEnergy)
abs(rstudent(resEnergy))[abs(rstudent(resEnergy))>2]
shapiro.test(resEnergy$residuals)

dfEnergy2 = dfEnergy[-c(1,2,3,4),]
resEnergy = lm(sqrt(TWhEnergy) ~ Year,dfEnergy2)
plot(resEnergy)
abs(rstudent(resEnergy))[abs(rstudent(resEnergy))>2]
shapiro.test(resEnergy$residuals)

bptest(resEnergy)
ncvTest(resEnergy)

par(mfrow=c(1,1))
plot(dfEnergy2$Year,sqrt(dfEnergy2$TWhEnergy))
abline(resEnergy,col = "red",lwd = 2)

#EXPORT
names(dfPop2)[names(dfPop2) == "Population"] = "World population in billion"
write.csv(dfPop2,"population_fitted.csv", row.names = TRUE)
write(paste(c("b,","a,"),resPop$coefficients),file="population_fitted.csv",append=TRUE)

names(dfGDP)[names(dfGDP) == "GDP"] = "World GDP in trillion of $"
write.csv(dfGDP,"gdp_fitted.csv", row.names = TRUE)
write(paste(c("b,","a,"),resGDP$coefficients),file="gdp_fitted.csv",append=TRUE)

names(dfCO22)[names(dfCO22) == "GtCO2"] = "World CO2 emission in billion of Tons"
write.csv(dfCO22,"co2_fitted.csv", row.names = TRUE)
write(paste(c("b,","a,"),resCO2$coefficients),file="co2_fitted.csv",append=TRUE)

names(dfEnergy2)[names(dfEnergy2) == "TWhEnergy"] = "World energy consumption in thousand of TWh"
write.csv(dfEnergy2,"energy_fitted.csv", row.names = TRUE)
write(paste(c("b,","a,"),resEnergy$coefficients),file="energy_fitted.csv",append=TRUE)
