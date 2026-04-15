import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt

st.set_page_config(layout="wide", page_title="VHI Analysis")

st.title("Аналіз VHI / VCI / TCI (Лабораторна 5)")

@st.cache_data
def load_data():
    df = pd.read_csv("data/vhi_data.csv") 
    df.columns = df.columns.str.strip()
    return df

df = load_data()

left_col, right_col = st.columns([1, 3])

with left_col:
    st.header("Параметри")
    
    # Dropdown для індексу
    index_type = st.selectbox("Оберіть індекс", ["VHI", "VCI", "TCI"])
    
    # Dropdown для області
    region = st.selectbox("Оберіть область", sorted(df["region"].unique()))
    
    # Slider для років
    min_year, max_year = int(df["year"].min()), int(df["year"].max())
    year_range = st.slider("Інтервал років", min_year, max_year, (min_year, max_year))
    
    # Slider для тижнів
    week_range = st.slider("Інтервал тижнів", 1, 52, (1, 52))
    
    # Checkboxes для сортування
    st.write("Сортування:")
    sort_asc = st.checkbox("За зростанням ↑")
    sort_desc = st.checkbox("За спаданням ↓")
    
    # Логіка чекбоксів 
    if sort_asc and sort_desc:
        st.warning("Оберіть лише один тип сортування!")

    # Кнопка Reset 
    if st.button("Скинути всі фільтри"):
        st.rerun()

filtered = df[
    (df["region"] == region) &
    (df["year"].between(year_range[0], year_range[1])) &
    (df["week"].between(week_range[0], week_range[1]))
].copy()

filtered["period"] = filtered["year"].astype(str) + "-w" + filtered["week"].astype(str)
filtered = filtered.sort_values(["year", "week"])

table_data = filtered.copy()
if sort_asc and not sort_desc:
    table_data = table_data.sort_values(by=index_type, ascending=True)
elif sort_desc and not sort_asc:
    table_data = table_data.sort_values(by=index_type, ascending=False)

with right_col:
    tab1, tab2, tab3 = st.tabs(["📊 Таблиця", "📈 Графік часового ряду", "🌍 Порівняння областей"])

    with tab1:
        st.subheader(f"Дані для області {region}")
        st.dataframe(table_data, use_container_width=True)

    with tab2:
        st.subheader(f"Динаміка {index_type}")
        if not filtered.empty:
            fig, ax = plt.subplots(figsize=(10, 5))
            ax.plot(filtered["period"], filtered[index_type], marker='o', markersize=2)
            ax.set_xticks(ax.get_xticks()[::5]) 
            plt.xticks(rotation=45)
            ax.set_ylabel(index_type)
            ax.grid(True, alpha=0.3)
            st.pyplot(fig)
        else:
            st.info("Дані відсутні для вибраного діапазону")

    with tab3:
        st.subheader(f"Порівняння {region} з іншими областями")
        fig, ax = plt.subplots(figsize=(10, 6))
        
        comparison_df = df[
            (df["year"].between(year_range[0], year_range[1])) &
            (df["week"].between(week_range[0], week_range[1]))
        ]
        
        for r in comparison_df["region"].unique():
            subset = comparison_df[comparison_df["region"] == r].sort_values(["year", "week"])
            subset["period"] = subset["year"].astype(str) + "-w" + subset["week"].astype(str)
            
            if r == region:
                ax.plot(subset["period"], subset[index_type], label=r, linewidth=3, color='red', zorder=5)
            else:
                ax.plot(subset["period"], subset[index_type], alpha=0.2, color='gray')
        
        ax.set_xticks(ax.get_xticks()[::10])
        plt.xticks(rotation=45)
        ax.set_title(f"Червона лінія: {region}")
        st.pyplot(fig)